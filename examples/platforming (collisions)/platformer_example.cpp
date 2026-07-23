// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include "platformer_example.h"

static Uint64 frame = 0;


bool is_airborne = false;

const bool* keyboardState = SDL_GetKeyboardState(nullptr);   // Reminder for self: We use NULL in C, and we use nullptr in C++




// consumes     std::vector<SDL_FRect> your_obstacles_here
// and          std::array <int, 2> current_player_pos = {0, 0};
//
// Should be pretty self explanatory:
// If there are no current collisions, then the player is airborne.
// TODO: Include grounded check too.
bool check_airborne(){

    bool res = false;
    
    Uint32 your_obstacles_amount = your_obstacles_here.size();

    for (int i = 0; i < your_obstacles_amount; i++){

        if ((supermotor::collidingVertices(Player, your_obstacles_here[i])).size() == 0){       // your_obstacles_here[i] is the current_obstacle.
            // SDL_Log("is airborne: true");
            res = true;
        }
    }

    return res;
}


void vertical_velocity_decay() {
    if (is_airborne){
        vertical_velocity += gravity;
    } else {
        vertical_velocity = 0.0f;
    }
}




// See https://wiki.libsdl.org/SDL3/BestKeyboardPractices and https://wiki.libsdl.org/SDL3/SDL_Scancode
void process_vertical_movement(){


    // Up arrow key.
    if (keyboardState[SDL_SCANCODE_UP]) {   
		// Player moves to the right :3
		vertical_velocity = -10.0f;
    }
}






void process_horizontal_movement(){


    // Left arrow key.
    if (keyboardState[SDL_SCANCODE_LEFT]) {
		// Player moves to the right :3
		horizontal_velocity -= 15.0f;
    }


    // Down arrow key.
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
       	// Player moves to the left :3
		horizontal_velocity += 15.0f;
	}
}








void update_player_pos() {

    // Stores player pos from the previous frame (for collision handling purposes).
    Previous_player_pos = Current_player_pos;        // Previous_player_pos <--- Current_player_pos




    // From here on... Current_player_pos <--- New_player_pos

    process_vertical_movement();
    process_horizontal_movement();

    Current_player_pos.move_x(horizontal_velocity);
    Current_player_pos.move_y(vertical_velocity);

    horizontal_velocity = 0;
    // vertical_velocity = 0;

    vertical_velocity_decay();      // You can refactor this to use "float gravity" or "double gravity" as a parameter here if you want.

    SDL_Log("\n");
    SDL_Log("Before: %d", Current_player_pos.get_top_left_corner_y());
    Current_player_pos = supermotor::handle_collisions(Previous_player_pos, Current_player_pos, your_obstacles_here);
    SDL_Log("After: %d", Current_player_pos.get_top_left_corner_y());

    Player = supermotor::copy_supermotor_rect_to_sdl_rect(Current_player_pos, Player);
    SDL_Log("Current_player_pos_#2: %f", Player.y);
}






struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* playerTexture;
    
    bool running = true;

    // SDL_Surface* mSurface;

    // Constructor
    SDL_Application(const char* title){
	    SDL_Init(SDL_INIT_VIDEO);
	    mWindow = SDL_CreateWindow(title, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);    
	    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
	    if (mRenderer == nullptr){
		    assert (0 && "ERROR: Hardware acceleration not supported :c");
	    } else {
		    SDL_Log("Current renderer: %s", SDL_GetRendererName(mRenderer));
		    SDL_Log("Available renderer drivers:");
		    for (int i = 0; i > SDL_GetNumRenderDrivers(); i++) {
			    SDL_Log("%d, %s", i + 1, SDL_GetRenderDriver(i));
		    }
            SDL_SetRenderLogicalPresentation(mRenderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	    }


	    SDL_Surface* player_surface = SDL_LoadPNG("./silly_thing.png");
	    if (player_surface == nullptr){
		    assert (0 && "ERROR: File not found :c");
	    }
        
        playerTexture = SDL_CreateTextureFromSurface(mRenderer, player_surface);

        SDL_DestroySurface(player_surface);

    }
	// Destructor
	~SDL_Application(){
		SDL_Quit();
	}


	
	void Input(){
		SDL_Event event;

		while (SDL_PollEvent(&event)){
			if (event.type == SDL_EVENT_QUIT){
				running = false;
			} else if (event.type == SDL_EVENT_KEY_DOWN) {

                // SDL_Log("CONGRATULA!!! You pressed the %d key :3)7", event.button.button);

                if (event.button.button == 41){          // 41 is the escape key       (you can remap it if you want :3)
                    SDL_Quit();
                }

                if (event.button.button == 7){          // 41 is the D key       (you can remap it if you want :3)
                    
                    
                    SDL_Log("Player.x: %f", Player.x);
                    SDL_Log("Player.y: %f", Player.y);
                    SDL_Log("Player.w: %f", Player.w);
                    SDL_Log("Player.h: %f", Player.h);
                    

                    SDL_Log("Horizontal velocity: %f", horizontal_velocity);
                    SDL_Log("Vertical velocity: %f", vertical_velocity);
                }
            }
		}
	}

   
	void Update(){

        is_airborne = check_airborne();

        update_player_pos();
	}

    

	void Render(){
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        SDL_RenderFillRect(mRenderer, &Background);


        // SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderTexture(mRenderer, playerTexture, nullptr, &Player);                // Renders the player.

        
        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
        Uint32 your_obstacles_amount = your_obstacles_here.size();
        for (int i = 0; i < your_obstacles_amount; i++){
    		SDL_RenderFillRect(mRenderer, &your_obstacles_here[i]);                           // Renders the obstacles.
        }
        

		// draw other things here ...		


		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(){

        SDL_Log("\n");
        SDL_Log("current_frame: %ld", frame);
        if (frame > 34){
            SDL_Quit();
            exit(0);
        }

		Input();
		Update();
		Render();

        frame++;
	}

	void MainLoop(){
		Uint64 fps = 0;
		Uint64 lastTime = 0;
		while(running){
			Uint64 currentTick = SDL_GetTicks();
			Tick();
			fps++;

			Uint64 deltaTime = SDL_GetTicks() - currentTick;
            if (deltaTime < 16.6){
                SDL_Delay(16.6 - deltaTime);
            }
			if (currentTick > lastTime + 1000) {
				lastTime = currentTick;
				std::string title;
				title += "Current FPS: " + std::to_string(fps);
				SDL_SetWindowTitle(mWindow, title.c_str());
				fps = 0;
			}
		}
	}
};


// Entry Point
int main(int argc, char* argv[]){

    your_obstacles_here.push_back(Obstacle1);
    your_obstacles_here.push_back(Obstacle2);
    your_obstacles_here.push_back(Obstacle3);
    your_obstacles_here.push_back(Obstacle4);

    SDL_Log("Player.x: %f", Player.x);
    SDL_Log("Player.y: %f", Player.y);
    SDL_Log("Player.w: %f", Player.w);
    SDL_Log("Player.h: %f", Player.h);

	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

