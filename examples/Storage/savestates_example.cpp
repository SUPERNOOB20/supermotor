// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ savestates_example.cpp -O3 -o example `pkg-config --libs --cflags sdl3`

// .
// .
// .



#include "../../supermotor/essentials/spritesheet_loader.h"

#include "savestates_example.h"





SDL_Renderer* mRenderer;
SDL_Texture* akyuuTexture;

std::vector<SDL_FRect> akyuu_poses;

Uint64 frame_counter;


/*
// typedef std::vector<std::tuple<SDL_Texture*, SDL_FRect>> sprite;
// typedef std::vector<sprite> sprites;
// sprites my_akyuus;
std::vector<std::tuple<SDL_Texture*, SDL_FRect>> my_akyuus;


void init_akyuu_instances() {

    std::tuple<SDL_Texture*, SDL_FRect> akyuu1(akyuuTexture, akyuu1_position);
    std::tuple<SDL_Texture*, SDL_FRect> akyuu2(akyuuTexture, akyuu2_position);

    my_akyuus[0] = akyuu1;
    my_akyuus[1] = akyuu2;

    
    // std::get<0>(my_akyuus[0]) = akyuuTexture;   // TODO: Flip this one horizontally!
    // std::get<0>(my_akyuus[1]) = akyuuTexture;

    // std::get<1>(my_akyuus[0]) = akyuu1_position;
    // std::get<1>(my_akyuus[1]) = akyuu2_position;
    
}
*/




// Returns the corresponding sprite to render according to my silly animation :3
//
// Uint8 akyuu_anim(Uint64 frame_counter)
//
constexpr int akyuu_anim_frame_screentime = 30;     // Customizable anim speed :3
Uint8 akyuu_anim(){

    int i = 0;

    if ((frame_counter % (akyuu_anim_frame_screentime * 2)) >= (akyuu_anim_frame_screentime)) {
        i = 1;
    }


    return i;
}




struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Texture* my_background;

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


        SDL_Surface* my_background_surface = SDL_LoadPNG("./Assets/background.png");
        my_background = SDL_CreateTextureFromSurface(mRenderer, my_background_surface);
        SDL_DestroySurface(my_background_surface);
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

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        SDL_RenderFillRect(mRenderer, &Background);



		SDL_RenderTexture(mRenderer, my_background, nullptr, &Background);        

        // akyuu_anim();
		SDL_RenderTexture(mRenderer, akyuuTexture, &akyuu_poses[akyuu_anim()], &akyuu1_position);
		SDL_RenderTexture(mRenderer, akyuuTexture, &akyuu_poses[akyuu_anim()], &akyuu2_position);


		// draw other things here ...

		
        // SDL_SetTextureScaleMode(akyuuTexture, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(akyuuTexture, SDL_SCALEMODE_LINEAR);            // For high definition textures (features interpolation and antialiasing).

		SDL_RenderPresent(mRenderer);
	}


    // Every tick is one iteration of the game loop.
	void Tick(){
		Input();
		Update();
		Render();
	}


	void MainLoop(){
        SDL_SetTextureScaleMode(akyuuTexture,  SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).
        SDL_SetTextureScaleMode(my_background, SDL_SCALEMODE_NEAREST);        // For pixel-art textures (no interpolation or antialiasing).

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

    akyuuTexture = supermotor::create_spritesheet(mRenderer, "./Assets/akyuu.bmp", 0x00, 0xFF, 0x00);
    akyuu_poses = supermotor::load_spritesheet(akyuuTexture, 32, 32, VERTICAL);
    assert((akyuu_poses.size()) == 2);


    // init_akyuu_instances();      // I tried, but couldn't get the "global tuples" working properly e.e (because the tuples need to be global but the SDL_FRects need to be initialized after SDL_Init, so not globally... @.@)


	app.MainLoop();
	return 0;
}




// Uint32 transparent_colour

