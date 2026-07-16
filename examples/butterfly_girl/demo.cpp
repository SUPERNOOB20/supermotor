// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ demo.cpp -O3 -o mariposa_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include <SDL3/SDL.h>
#include <string>
#include <cassert>

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT   720
#include "supermotor/essentials/animate.h"
#include "supermotor/essentials/atlas.h"



//   Overwrite these two values with the resolution of your assets
//  (For example: mine here is 900x1600)
//  (Usually this would be filled automatically, but... e.e)
static float texture_width = 900.0f;
static float texture_height = 1600.0f;

SDL_FRect a_dst_rect;
a_dst_rect.x = 0.0f
a_dst_rect.y = 0.0f
a_dst_rect.w = texture_width;
a_dst_rect.h = texture_height;

SDL_FRect b_dst_rect;
b_dst_rect.x = 0.0f
b_dst_rect.y = 0.0f
b_dst_rect.w = texture_width;
b_dst_rect.h = texture_height;

SDL_FRect c_dst_rect;
c_dst_rect.x = 0.0f
c_dst_rect.y = 0.0f
c_dst_rect.w = texture_width;
c_dst_rect.h = texture_height;




void bubbles(deltaTime){
    a = animation_loop("vertical", bubbles_I_surface, "bubbles_I_f.png", deltaTime);
    b = animation_loop("vertical", bubbles_II_surface, "bubbles_II_f.png", deltaTime);
    c = animation_loop("vertical", bubbles_III_surface, "bubbles_III_f.png", deltaTime);

    SDL_RenderTexture(mRenderer, a, nullptr, nullptr);
    SDL_RenderTexture(mRenderer, b, nullptr, nullptr);
	SDL_RenderTexture(mRenderer, c, nullptr, nullptr);
}

void stars(deltaTime){
    // animation_loop ("horizontal", stars_surface, "stars.png", deltaTime)        < --- Scrapped idea, sorry.
   // ...
}




struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* bgTexture;
    SDL_Texture* bubbles_I_texture;
    SDL_Texture* bubbles_II_texture;
    SDL_Texture* bubbles_III_texture;
    
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

	    // SDL_Surface* surface = SDL_LoadJPG("./background_asset.jpeg");        < --- This doesn't work e.e so I decided to convert to .png instead...
        SDL_Surface* surface = SDL_LoadPNG("./background_asset.png");

	    if (surface == nullptr){
		    assert(0 && "ERROR: File not found :c");
	    }
	    bgTexture = SDL_CreateTextureFromSurface(mRenderer, surface);


	    SDL_Surface* bubbles_I_surface   = SDL_LoadPNG("./bubbles_I.png");
	    SDL_Surface* bubbles_II_surface  = SDL_LoadPNG("./bubbles_II.png");
	    SDL_Surface* bubbles_III_surface = SDL_LoadPNG("./bubbles_III.png");

	    bubbles_I_texture   = SDL_CreateTextureFromSurface(mRenderer, bubbles_I_surface);
	    bubbles_II_texture  = SDL_CreateTextureFromSurface(mRenderer, bubbles_II_surface);
	    bubbles_III_texture = SDL_CreateTextureFromSurface(mRenderer, bubbles_III_surface);
        

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

   
	void Update(){
	}


	void Render(Uint64 deltaTime){

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
		SDL_RenderClear(mRenderer);

		SDL_RenderTexture(mRenderer, bgTexture, nullptr, nullptr);

        bubbles(deltaTime);
        stars(deltaTime);

		// draw other things here ...
		
        // SDL_SetTextureScaleMode(bgTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        SDL_SetTextureScaleMode(bgTexture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).

		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(Uint64 deltaTime){
		Input();
		Update();
		Render(deltaTime);
	}

	void MainLoop(){
		Uint64 fps = 0;
		Uint64 lastTime = 0;
		while(running){
			Uint64 currentTick = SDL_GetTicks();
			Tick(Uint64 deltaTime);
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

