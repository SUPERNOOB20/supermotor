// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ storage_demo.cpp -O3 -o my_game_with_saving_system `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include "storage_demo.h"



// Switch to false if you don't want VSync.
// Oh yeah btw I called it VSync for simplicity, but all it does is just capping you at 60fps (it's not real, real VSync ":3)
bool vsync = true;



enum Action {
    NO_ACTION,   // 0
    ṔAINT,       // 1
    ERASE        // 2
};
unsigned short int current_action = 0;


SDL_Texture* canvas;            // Your drawing will get saved here.




struct SDL_Application{

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
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
    }
	// Destructor
	~SDL_Application(){
		SDL_Quit();
	}



	




	
	void Input(){

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			} else {

    
                SDL_MouseButtonFlags current_mouse_action = SDL_GetGlobalMouseState(&mouse_pos_x, &mouse_pos_y);      // Updates mouse pos (every frame, ofc! :3).

                

                if (current_mouse_action == SDL_BUTTON_LMASK) {               // If player is holding left  click: paint! :3
                    current_action = 1;
                } else if (current_mouse_action == SDL_BUTTON_RMASK) {      //  If player is holding right click: erase! :3
                    current_action = 2;
                } else {
                    current_action = 0;                                   //    If player is not holding left click or right click, don't do anything... (resets current_action, so to say! "^^)
                }

                if (event.type == SDL_EVENT_KEY_DOWN) {

                    // SDL_Log("CONGRATULA!!! You pressed the %d key :3)7", event.button.button);
                        
                    


                    if (event.button.button == 21) {             // Press the R key to reset your canvas. 

                        // --- PROLOGUE (STORE) ----
                        SDL_Texture* your_previous_render_target = SDL_GetRenderTarget(mRenderer);


                        // --- CLEAR ----
                        SDL_SetRenderTarget(mRenderer, canvas);     // Erases your whole canvas! (Effectively "resetting" it).
                        SDL_RenderClear(mRenderer);


                        // --- EPLIOGUE (RESTORE) ----
                        SDL_SetRenderTarget(mRenderer, your_previous_render_target);
                    }




                    
                    if (event.button.button == 22) {             // Press the S key to save your canvas.
                        void* voidedCanvas = (void*) canvas;
                        void* savedData = SDL_malloc(sizeof(voidedCanvas));
                        savedData = (void*) voidedCanvas;
                        // saveLen = sizeof(savedData);
                        supermotor::storage::WriteSave("my_lovely_canvas.dat", savedData);
                    }

                    if (event.button.button == 15) {             // Press the L key to load your canvas.
                        void* loaded_data = supermotor::storage::ReadSave("my_lovely_canvas.dat");
                        canvas = (SDL_Texture*) (loaded_data);
                    }

                    /*
                    if (event.button.button == 41) {             // P key
                        game_is_paused = !game_is_paused;        // Pause <---> Unpause.
                    }
                    */


                    if (event.button.button == 41){          // 41 is the escape key       (you can remap it if you want :3)
                        SDL_Quit();     // Exits SDL.
                        exit(0);       //  Taskkill.
                    }


                    /*
                    // Debug.
                    if (event.button.button == 7){          // 7 is the D key       (you can remap it if you want :3)
                        
                        SDL_Log("\n"); 
                        SDL_Log("Current action: %d.", current_action);
                        // SDL_Log("Current frame: %ld", frame);
                       
                    }
                    */

                }                    
            }
		}
	}

   
	void Update(){
        // SDL_GetGlobalMouseState(float &mouse_pos_x, float &mouse_pos_y);      // Updates mouse pos (every frame, ofc! :3).

        Brush.x = mouse_pos_x  +  MOUSE_CENTER;
        Brush.y = mouse_pos_y  +  MOUSE_CENTER;
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);            // Pro tip: Use SDL_SetRenderDrawColor with black (or don't use it at all) before SDL_RenderClear if you're on LETTERBOX logical presentation (which we are)
		// SDL_RenderClear(mRenderer);  // Don't clean, keep it dirty :3

		// SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
        // SDL_RenderFillRect(mRenderer, &Background);

		switch(current_action) {

            case 1:
                SDL_SetRenderTarget(mRenderer, canvas);     // Paint! (Renders to canvas)

                SDL_SetRenderDrawColor(mRenderer, BRUSH_COLOR_R, BRUSH_COLOR_G, BRUSH_COLOR_B, 0xFF);
                SDL_RenderFillRect(mRenderer, &Brush);

                SDL_SetRenderTarget(mRenderer, nullptr);    // Back to normal... (resume rendering on window)
            break;


            case 2:
                SDL_SetRenderTarget(mRenderer, canvas);     // Erase! (Renders to canvas)

                SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(mRenderer, &Brush);

                SDL_SetRenderTarget(mRenderer, nullptr);    // Back to normal... (resume rendering on window)
            break;
        }

        SDL_RenderTexture(mRenderer, canvas, nullptr, nullptr);
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

