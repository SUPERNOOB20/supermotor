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

    previous_player_pos = current_player_pos;        // previous_player_pos <--- current_player_pos



    // From here on... current_player_pos <--- new_player_pos

    Player.x += vertical_velocity;

    vertical_velocity_decay();      // You can use "float gravity" or "double gravity" as a parameter here if you want.

    supermotor::handle_collisions(previous_player_pos, current_player_pos, obstacles);
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
        current_obstacle = your_obstacles_here[i];
        dummy_current_obstacle = current_obstacle;
        supermotor::dummy_current_obstacle.move_y(-1);  // Remember that our origin (0, 0) is the top-left corner of the screen.

        if ((supermotor::collidingVertices(Player, current_obstacle).size = 0) && (supermotor::collidingVertices(Player, dummy_current_obstacle).size > 0)){ 
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
		    assert(0 && "ERROR: File not found :c");
	    }
        
        playerTexture = SDL_CreateTextureFromSurface(mRenderer, player_surface);
	    your_textures_here.push_back(playerTexture);

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

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
		SDL_RenderClear(mRenderer);

        /* Why is foreach so buggy in C++...? x.x
           You can fix it if you want, but I'd rather save myself the struggle. Let's do it with a good old for loop instead.

        for (SDL_Texture* texture : your_textures_here){
    		SDL_RenderTexture(mRenderer, texture, nullptr, nullptr);

            // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
            SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).
        }
        */
        Uint32 your_textures_amount = your_textures_here.size();
        for (int i = 0; i < your_textures_amount; i++){
    		SDL_RenderTexture(mRenderer, your_textures_here[i], nullptr, nullptr);

            // SDL_SetTextureScaleMode(your_textures_here[i], SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
            SDL_SetTextureScaleMode(your_textures_here[i], SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).
        }


		// draw other things here ...		


		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(){
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
	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

