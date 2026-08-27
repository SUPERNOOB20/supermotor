// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ demo.cpp -O3 -o my_game `pkg-config --libs --cflags sdl3`

// .
// .
// .


#define ENEMY_SIZE_SCALE (8)
#define ANIMATION_DURATION_IN_SECONDS (1.0f)


#include "despawn_demo.h"




Uint64 frame_counter;
SDL_FRect enemy_dst_rect;





// Returns the corresponding sprite to render according to my silly animation :3
//
// Uint8 enemy_anim(Uint64 frame_counter)
//
Uint8 enemy_anim(){

    int f = frame_counter % ( (int)(ANIMATION_DURATION_IN_SECONDS * 60.0f) );        // I'm assuming 60fps here.
    int i = 0;

    if (f < ANIMATION_DURATION_IN_SECONDS * 60.0f / 2.0f) {
        i = 1;
    }



    return i;
}








// Switch to false if you don't want VSync.
// Oh yeah btw I called it VSync for simplicity, but all it does is just capping you at 60fps (it's not real, real VSync ":3)
bool vsync = true;


typedef std::vector<SDL_FRect> poses;

SDL_Texture* enemy_texture;
poses enemy_poses;





struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    
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
			}
		}
	}

   
	void Update(Uint64 frame_counter){
		
		Uint64 number_of_transient_objects = projectiles.size();
		for (int i = 0; i < number_of_transient_objects; i++) {
			despawn_check();
		}
		
		if ((frame_counter %  PROJECTILE_SPAWN_RATE) == 0) {
			Projectile my_projectile();					// Generate a new proiejctile.
			projectiles.push_back(my_projectile);		// Add it to our list of projectiles.
		}
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        SDL_RenderFillRect(mRenderer, &Background);


		SDL_RenderTexture(mRenderer, enemy_texture, &enemy_poses[enemy_anim()], &enemy_dst_rect);

		Uint64 number_of_projectiles = projectiles.size();
		for (int i = 0; i < number_of_projectiles; i++) {
			SDL_RenderTexture(mRenderer, projectiles[i], nullptr, nullptr);
		}
		
		// draw other things here ...
		
        SDL_SetTextureScaleMode(enemy_texture, SDL_SCALEMODE_NEAREST);         // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(enemy_texture, SDL_SCALEMODE_LINEAR);      //  For high definition textures (features interpolation and antialiasing).

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

        enemy_texture = supermotor::create_spritesheet(mRenderer, "./Assets/fairy.png", 0xFF, 0x00, 0xFF);
        enemy_poses   = supermotor::load_spritesheet(enemy_texture, 32, 16, VERTICAL);

        enemy_dst_rect    =  screen_center_rect;

        int sprite_width = 32;
        int sprite_height = 16;

        enemy_dst_rect.x  -= sprite_width  * ENEMY_SIZE_SCALE / 2.0f;
        enemy_dst_rect.y  -= sprite_height * ENEMY_SIZE_SCALE / 2.0f;
        enemy_dst_rect.w  =  sprite_width  * ENEMY_SIZE_SCALE;
        enemy_dst_rect.h  =  sprite_height * ENEMY_SIZE_SCALE;






        /*
        enemy_dst_rect.x  -= enemy_texture -> w * ENEMY_SIZE_SCALE / 2.0f;
        enemy_dst_rect.y  -= enemy_texture -> h * ENEMY_SIZE_SCALE / 2.0f;
        enemy_dst_rect.w  =  enemy_texture -> w * ENEMY_SIZE_SCALE;
        enemy_dst_rect.h  =  enemy_texture -> h * ENEMY_SIZE_SCALE / 2.0f;
        */



		while(running){
			Uint64 currentTick = SDL_GetTicks();
			Tick();
			fps++;

			Uint64 deltaTime = SDL_GetTicks() - currentTick;


            if (vsync) {

                // Should be quite safe to assume deltaTime >= 0...
                if (deltaTime < 16.666666){    
                    SDL_Delay(16.666666 - deltaTime);       // Homemade VSync...            
                }
            }


			if (currentTick > lastTime + 1000) {
				lastTime = currentTick;
				std::string title;
				title += "Current FPS: " + std::to_string(fps);
				SDL_SetWindowTitle(mWindow, title.c_str());
				fps = 0;
			}

            frame_counter++;
		}
	}
};


// Entry Point
int main(int argc, char* argv[]){
    
	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

