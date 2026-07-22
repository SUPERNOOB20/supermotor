// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include "platformer_example.h"



void vertical_velocity_decay() {
    if (vertical_velocity < gravity) {
        vertical_velocity = 0.0f;
    } else if (vertical_velocity >= gravity) {
        vertical_velocity -= gravity;
    }
}

void update_player_pos() {

    Previous_player_pos = Current_player_pos;        // Previous_player_pos <--- Current_player_pos



    // From here on... Current_player_pos <--- New_player_pos

    Player.x += vertical_velocity;

    vertical_velocity_decay();      // You can use "float gravity" or "double gravity" as a parameter here if you want.

    supermotor::handle_collisions(Previous_player_pos, Current_player_pos, your_obstacles_here);

    Player = supermotor::copy_supermotor_rect_to_sdl_rect(&Current_player_pos, &Player);
}


// consumes     std::vector<SDL_FRect> your_obstacles_here
// and          std::array <int, 2> current_player_pos = {0, 0};
//
// Should be pretty self explanatory:
// If there is any (currently active) obstacle for which the player would collide
// if the obstacle was one pixel above, then the player is on the ground.
bool is_airborne(){

    bool res = true;

    Uint32 your_obstacles_amount = your_obstacles_here.size();
    for (int i = 0; i < your_obstacles_amount; i++){
        supermotor::Rect current_obstacle(your_obstacles_here[i]);
        supermotor::Rect dummy_current_obstacle(current_obstacle);
        dummy_current_obstacle.move_y(-1);  // Remember that our origin (0, 0) is the top-left corner of the screen.

        if (((supermotor::collidingVertices(Player, current_obstacle)).size() == 0) && ((supermotor::collidingVertices(Player, dummy_current_obstacle)).size() > 0)){ 
            res = false;
        }
    }

    return res;
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

                switch (event.button.button) {

	            	case 79:
	            		// Player moves to the right :3
	            		horizontal_velocity += 0.05f;
	            		break;
	            		
            		case 80:
                       	// Player moves to the left :3
            			horizontal_velocity -= 0.05f;
    			}
            }
		}
	}

   
	void Update(){

        is_airborne();

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
        // static Uint64 frame = 0;
        // SDL_Log("current_frame: %ld", frame);

		Input();
		Update();
		Render();
	}

	void MainLoop(){
		Uint64 fps = 0;
		Uint64 lastTime = 0;
		while(running){
			Uint64 currentTick = SDL_GetTicks();
			Tick();
			fps++;

			Uint64 deltaTime = SDL_GetTicks() - currentTick;
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

    // SDL_Log("Player.x: %f", Player.x);
    // SDL_Log("Player.y: %f", Player.y);
    // SDL_Log("Player.w: %f", Player.w);
    // SDL_Log("Player.h: %f", Player.h);

	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

