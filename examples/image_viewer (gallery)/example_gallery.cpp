// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ demo.cpp -O3 -o rgb_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include <SDL3/SDL.h>
#include <string>
#include <cassert>

#include "../../supermotor/core.h"
#include "../../supermotor/essentials/gallery.h"


#define WINDOW_WIDTH      640
#define WINDOW_HEIGHT     480

#define NUMBER_OF_IMAGES  4     // Override this with the number of images your gallery will have.


bool my_log = false;



std::vector<SDL_Texture*> your_textures_here;
int your_gallery = 0;





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


        std::string your_filenames_here[NUMBER_OF_IMAGES] = {"./YourImagesHere/Remilia.png", "./YourImagesHere/Yorihime.png", "./YourImagesHere/Youmu.png", "./YourImagesHere/Ascent.png"};
        your_textures_here = generate_textures(mRenderer, your_filenames_here, NUMBER_OF_IMAGES);

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
                my_log = true;

                if (event.button.button == 80){      
                    your_gallery--;      // Press the left key to move to the previous image.
                } else if (event.button.button == 79){          
                    your_gallery++;      // Press the right key to move to the next image.
                }
            }
        }
	}

   
	void Update(){
        your_gallery = supermotor::essentials::gallery_update(your_gallery, NUMBER_OF_IMAGES);
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
		SDL_RenderClear(mRenderer);

		// SDL_RenderTexture(mRenderer, mTexture, nullptr, nullptr);

        // for (int i = 0; i < sizeof(your_textures_here); i++){
        for (int i = 0; i < 4; i++){
            
            SDL_FRect texture_srcrect;
            texture_srcrect.x = (float) WINDOW_WIDTH  / 2.0f;
            texture_srcrect.y = (float) WINDOW_HEIGHT / 2.0f;
            texture_srcrect.w = (float) WINDOW_WIDTH  * 30.0f;
            texture_srcrect.h = (float) WINDOW_HEIGHT * 30.0f;

            SDL_RenderTexture(mRenderer, your_textures_here[your_gallery], &texture_srcrect, nullptr);
            // SDL_SetTextureScaleMode(your_textures_here[i], SDL_SCALEMODE_LINEAR);            // Optional step - for high definition textures (features interpolation and antialiasing).
            // SDL_SetTextureScaleMode(your_textures_here[i], SDL_SCALEMODE_NEAREST);          //  Optional step - for pixel art (nearest neighbour scaling — no interpolation or antialiasing).
        }

        // SDL_RenderTexture(mRenderer, your_textures_here[i], nullptr, nullptr);

		// draw other things here ...
		
        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).

		SDL_RenderPresent(mRenderer);
	}

    // Every tick is one iteration of the game loop.
	void Tick(){
		Input();
		Update();
		Render();

        if (my_log == true){
            SDL_Log("current gallery item ID: %d", your_gallery);
            my_log = false;
        }
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

