// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#define PLAYER_SIZE 1       // Scale the player!!! 1 just means normal size... zzz


// set_player_size(45 * PLAYER_SIZE,  98 * PLAYER_SIZE);
#define player_texture_width 45
#define player_texture_height 98
#include "platformer_example.h"

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

                /*
                // Debug.
                if (event.button.button == 7){          // 7 is the D key       (you can remap it if you want :3)
                    
                    SDL_Log("\n");
                    
                    SDL_Log("Current frame: %ld", frame);
                    SDL_Log("Player.x: %f", Player.x);
                    SDL_Log("Player.y: %f", Player.y);
                    SDL_Log("Player.w: %f", Player.w);
                    SDL_Log("Player.h: %f", Player.h);
                    
                    SDL_Log("Horizontal velocity: %f", horizontal_velocity);
                    SDL_Log("Vertical velocity: %f", vertical_velocity);

                    SDL_Log("frames_since_started_jumping: %d", frames_since_started_jumping);
                    SDL_Log("is airborne: %d", is_airborne);
                    
                }
                */

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

