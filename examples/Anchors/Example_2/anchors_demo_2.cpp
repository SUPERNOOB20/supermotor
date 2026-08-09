// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ anchors_demo.cpp -O3 -o my_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include "anchors_demo_2.h"

#define IMAGE_SCALE_DOWN_FACTOR 15

#define NUMBER_OF_STATES 9      // 9 anchors.

#define MY_IMAGE_WIDTH   320
#define MY_IMAGE_HEIGHT  180

#define MINI_WIDTH    (MY_IMAGE_WIDTH   /  IMAGE_SCALE_DOWN_FACTOR)
#define MINI_HEIGHT   (MY_IMAGE_HEIGHT  /  IMAGE_SCALE_DOWN_FACTOR)

int my_gallery = 0;


SDL_FRect my_image_dst_rect {
    .x = 0,
    .y = 0,
    .w = MINI_WIDTH,
    .h = MINI_HEIGHT
};



// Switch to false if you don't want VSync.
// Oh yeah btw I called it VSync for simplicity, but all it does is just capping you at 60fps (it's not real, real VSync ":3)
bool vsync = true;



struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    
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

	    SDL_Surface* surface = SDL_LoadPNG("../beautiful_car.png");
	    if (surface == nullptr){
		    assert(0 && "ERROR: File not found :c");
	    }
        
        // SDL_Surface* mini_surface = SDL_ScaleSurface(surface, (surface->w / IMAGE_SCALE_DOWN_FACTOR), (surface->h / IMAGE_SCALE_DOWN_FACTOR), SDL_SCALEMODE_LINEAR);

        SDL_Surface* mini_surface = SDL_ScaleSurface(surface, MINI_WIDTH, MINI_HEIGHT, SDL_SCALEMODE_LINEAR);

        SDL_DestroySurface(surface);

	    mTexture = SDL_CreateTextureFromSurface(mRenderer, mini_surface);

        SDL_DestroySurface(mini_surface);
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

                if (event.button.button == 20) {    // Press the Q key to move to the previous image.
                    my_gallery--;
                }

                if (event.button.button == 8) {     // Press the E key to move to the previous image.
                    my_gallery++;
                }

                if (event.button.button == 41){          // 41 is the escape key       (you can remap it if you want :3)
                    SDL_Quit();     // Exits SDL.
                    exit(0);       //  Taskkill.
                }
            }
		}
	}

   
	void Update(){
        my_gallery = supermotor::essentials::gallery_update(my_gallery, NUMBER_OF_STATES);
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        SDL_RenderFillRect(mRenderer, &Background);


		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x44, 0x88);
        SDL_RenderFillRect(mRenderer, &Container);


        SDL_FRect current_anchor = supermotor::gui::anchor(my_gallery, my_image_dst_rect, Container);
		SDL_RenderTexture(mRenderer, mTexture, nullptr, &current_anchor);


		// draw other things here ...

		
        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).

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
		}
	}
};


// Entry Point
int main(int argc, char* argv[]){
	SDL_Application app("FPS test! Current FPS: ");
	app.MainLoop();
	return 0;
}

