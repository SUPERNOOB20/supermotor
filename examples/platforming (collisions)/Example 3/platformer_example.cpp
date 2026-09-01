// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .


#include "platformer_example.h"




struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* playerTexture;
    SDL_Texture* iceTexture;
    
    bool running = true;

    SDL_Surface* player_surface;
    SDL_Surface* ice_surface;

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


	    player_surface = SDL_LoadPNG("../Assets/silly_thing.png");
	    if (player_surface == nullptr){
		    assert (0 && "ERROR: Player file 'silly_thing.png' not found :c");
	    }
        playerTexture = SDL_CreateTextureFromSurface(mRenderer, player_surface);
        SDL_DestroySurface(player_surface);


        ice_surface = SDL_LoadBMP("../Assets/ice.bmp");
	    if (player_surface == nullptr){
		    assert (0 && "ERROR: Obstacle file 'ice.bmp' not found :c");
	    }
        iceTexture = SDL_CreateTextureFromSurface(mRenderer, ice_surface);
        SDL_DestroySurface(ice_surface);
        

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
                    SDL_Quit();     // Exits SDL.
                    exit(0);       //  Taskkill.
                }


                
                // Debug.
                if (event.button.button == 9){          // 9 is the F key       (you can remap it if you want :3)
                    
                    SDL_Log("\n");

                                        
                    SDL_Log("Current frame: %ld", frame);
                    SDL_Log("Player.x: %f", Player.x);
                    SDL_Log("Player.y: %f", Player.y);
                    SDL_Log("Player.w: %f", Player.w);
                    SDL_Log("Player.h: %f", Player.h);
                    
                    SDL_Log("frames_since_started_jumping: %d", frames_since_started_jumping);
                    SDL_Log("is airborne: %d", is_airborne);

                    
                    SDL_Log("Horizontal velocity: %f", horizontal_velocity);
                    SDL_Log("Vertical velocity: %f", vertical_velocity);
                }
                

            }
		}
	}



	void Update(){
        supermotor::platforming::update_platforming_state();
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
        

        Uint32 your_ice_obstacles_amount = supermotor::platforming::your_ice_obstacles_here.size();
        for (int i = 0; i < your_ice_obstacles_amount; i++){
    		SDL_RenderTexture(mRenderer, iceTexture, nullptr, &your_ice_obstacles_here[i]);                           // Renders the ice obstacles.
        }

		// draw other things here ...		


		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(){

        // SDL_Log("\n");
        // SDL_Log("current_frame: %ld", frame);

        /*
        if (frame > 34){
            SDL_Quit();
            exit(0);
        }
        */

		Input();
		Update();
		Render();

        update_nudge();

        // frame++;
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


    set_player_size(45 * PLAYER_SIZE,  98 * PLAYER_SIZE);


    your_obstacles_here.push_back(ObstacleFloor1);

    your_obstacles_here.push_back(ObstacleWall1);
    your_obstacles_here.push_back(ObstacleWall2);

    your_floor_obstacles_here = supermotor::platforming::your_obstacles_here;
    your_floor_obstacles_here.push_back(ObstacleIce1);

    your_ice_obstacles_here.push_back(ObstacleIce1);    

    SDL_Log("Player.x: %f", Player.x);
    SDL_Log("Player.y: %f", Player.y);
    SDL_Log("Player.w: %f", Player.w);
    SDL_Log("Player.h: %f", Player.h);

	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

