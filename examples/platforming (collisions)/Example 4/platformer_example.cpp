// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

// Example 4: Moving platforms

#include "platformer_example.h"






#define PLAYER_SIZE 1       // Scale the player!!! 1 just means normal size zzz...


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


	    SDL_Surface* player_surface = SDL_LoadPNG("../Assets/silly_thing.png");
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
                    SDL_Quit();     // Exits SDL.
                    exit(0);       //  Taskkill.
                }

                // Debug.
                if (event.button.button == 9){          // 9 is the F key       (you can remap it if you want :3)
                    
                    SDL_Log("\n");
                    
                    SDL_Log("Current frame: %ld", supermotor::platforming::frame);
                    SDL_Log("Player.x: %f",       supermotor::platforming::Player.x);
                    SDL_Log("Player.y: %f",       supermotor::platforming::Player.y);
                    SDL_Log("Player.w: %f",       supermotor::platforming::Player.w);
                    SDL_Log("Player.h: %f",       supermotor::platforming::Player.h);
                    
                    // SDL_Log("Horizontal velocity: %f", horizontal_velocity);
                    // SDL_Log("Vertical velocity: %f", vertical_velocity);

                    // SDL_Log("frames_since_started_jumping: %d", frames_since_started_jumping);
                    // SDL_Log("is airborne: %d", is_airborne);
                    
                }
            }
		}
	}


	inline void Update() { supermotor::platforming::update_platforming_state(); }       // Remove inline if you add more things to this function.
    

	void Render(){
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        SDL_RenderFillRect(mRenderer, &Background);


        // SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderTexture(mRenderer, playerTexture, nullptr, &supermotor::platforming::Player);                // Renders the player.

        
        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
        Uint32 your_obstacles_amount = supermotor::platforming::your_obstacles_here.size();
        for (int i = 0; i < your_obstacles_amount; i++){
    		SDL_RenderFillRect(mRenderer, &supermotor::platforming::your_obstacles_here[i]);                           // Renders the obstacles.
        }

        SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x7F, 0xFF);
        Uint32 your_moving_platforms_amount = supermotor::platforming::your_moving_platforms_here.size();

        // TODO
        for (int i = 0; i < your_moving_platforms_amount; i++){

            supermotor::MovingPlatform current_platform = supermotor::platforming::your_moving_platforms_here[i]; 

            SDL_Log("x: %d", current_platform.get_top_left_corner_x());

            SDL_FRect current_platform_sdl_rect;            
            current_platform_sdl_rect             = convert_moving_platform_to_sdl_rect(current_platform, current_platform_sdl_rect);

            // SDL_Log("x: %f", current_platform_sdl_rect.x);


    		SDL_RenderFillRect(mRenderer, &current_platform_sdl_rect);                           // Renders the moving platforms.
        }


		// draw other things here ...		


		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(){


        // SDL_Log("\n");
        // SDL_Log("current_frame: %ld", supermotor::platforming::frame);


        /*
        // Useful for debugging.
        if (supermotor::platforming::frame > 3){
            SDL_Quit();
            exit(0);
        }
        */

        SDL_Delay(1000);   // Useful for debugging.

		Input();
		Update();
		Render();

        update_nudge();
	}



	void MainLoop(){

        supermotor::platforming::Player.y -= WINDOW_HEIGHT * 0.2f;
        supermotor::platforming::Dummy_previous_player_pos.y -= (WINDOW_HEIGHT * 0.2f);
        supermotor::platforming::Previous_player_pos.move_y(-WINDOW_HEIGHT * 0.2f);
        supermotor::platforming::Current_player_pos.move_y(-WINDOW_HEIGHT * 0.2f);



		Uint64 fps = 0;
		Uint64 lastTime = 0;
		while(running){
            supermotor::platforming::frame++;
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



    supermotor::platforming::set_player_size(45 * PLAYER_SIZE,  98 * PLAYER_SIZE);



    // magic number: 3
    SDL_FRect all_obstacles[3] = {Obstacle1, Obstacle2, Obstacle3};
    unsigned int amount_of_obstacles = 3;

    for (int i = 0; i < amount_of_obstacles; i++){
        supermotor::platforming::your_obstacles_here.push_back(all_obstacles[i]);
    }

    supermotor::Rect SupermotorObstacle4 = supermotor::Rect(Obstacle4);       // Convert this "SDL Rect" to a "supermotor rect"...
    supermotor::Rect SupermotorObstacle5 = supermotor::Rect(Obstacle5);      //  Convert this "SDL Rect" to a "supermotor rect"...

    supermotor::MovingPlatform my_moving_platform1 ((double) 2.0f, (double) 0.0f, &SupermotorObstacle4);
    supermotor::MovingPlatform my_moving_platform2 ((double) 8.0f, (double) 0.0f, &SupermotorObstacle5);

    // magic number: 2
    supermotor::MovingPlatform all_moving_platforms[2] = {my_moving_platform1, my_moving_platform2};
    unsigned int amount_of_moving_platforms = 2;

    for (int i = 0; i < amount_of_moving_platforms; i++){
        supermotor::platforming::your_moving_platforms_here.push_back(all_moving_platforms[i]);
    }


    /*
    SDL_Log("Player.x: %f", supermotor::platforming::Player.x);
    SDL_Log("Player.y: %f", supermotor::platforming::Player.y);
    SDL_Log("Player.w: %f", supermotor::platforming::Player.w);
    SDL_Log("Player.h: %f", supermotor::platforming::Player.h);
    */


	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

