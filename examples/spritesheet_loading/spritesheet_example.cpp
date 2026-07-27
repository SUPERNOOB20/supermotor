// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ spritesheet_example.cpp -O3 -o example `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include <SDL3/SDL.h>
#include <string>
#include <cassert>

#include "../../supermotor/essentials/spritesheet_loader.h"

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT   720




SDL_Texture* cirnoTexture;
Uint64 frame_counter;

/*

// cirno_anim(int frame_counter);
// cirno_sprite.set_tiles(bn::sprite_items::cirno_spritesheet.tiles_item().create_tiles(3));
void cirno_anim(Uint64 frame_counter){

    bn::sprite_ptr cirno_sprite = bn::sprite_items::cirno_spritesheet.create_sprite(0, 0); 

    VRAM->global_sprites.push_back(cirno_sprite);

    int f = frame_counter % 470;
    int i = 0;

    if (f<=250) {
        if ((f % 50) > 25) {
            i = 1;
        }
    } else if (f > 350) {    // 350 < f < 470
        if ((f % 20) < 10) {
            i = 2;
        } else {
            i = 3;
        }
    }
        
    cirno_sprite.set_tiles(bn::sprite_items::cirno_spritesheet.tiles_item().create_tiles(i));

    return;
}

*/




struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    SDL_Surface* cirnoSurface;
    
    bool running = true;



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

	    cirnoSurface = SDL_LoadBMP("./Assets/cirno_spritesheet.bmp");
	    if (cirnoSurface == nullptr){
		    assert(0 && "ERROR: 'cirno_spriteseet.bmp' file not found :c");
	    }
	    cirnoTexture = SDL_CreateTextureFromSurface(mRenderer, cirnoSurface);
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
            }
		}
	}

   
	void Update(){
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
		SDL_RenderClear(mRenderer);
        
        // cirno_anim();
        
		SDL_RenderTexture(mRenderer, cirnoTexture, nullptr, nullptr);

		// draw other things here ...
		
        SDL_SetTextureScaleMode(cirnoTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(cirnoTexture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).

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
            if (deltaTime < 16.6){
                SDL_Delay(16.6 - deltaTime);        // Enforce 60fps.
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

    supermotor::load_spritesheet(cirnoTexture, 32, 32, VERTICAL);

	app.MainLoop();
	return 0;
}




// Uint32 transparent_colour

