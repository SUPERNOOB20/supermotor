// Credits to Mike Shah  -  https://youtu.be/yZl9X47cHi8
// g++ demo.cpp -O3 -o my_game `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include "../../supermotor/essentials/text.h"




#define WINDOW_WIDTH   1280.0f
#define WINDOW_HEIGHT   720.0f

#define TEXT_WIDTH (WINDOW_WIDTH/1.5f)           // You can change that 1.5f for           larger or smaller text.
#define LINE_SPACING (WINDOW_HEIGHT/12.0f)       //  You can change that 2.0f for text with larger or smaller gaps.

// Switch to false if you don't want VSync.
// Oh yeah btw I called it VSync for simplicity, but all it does is just capping you at 60fps (it's not real, real VSync ":3)
bool vsync = true;


SDL_Renderer* mRenderer;

TTF_Font* mFont                        =  nullptr;





std::vector<SDL_Texture*> my_text_textures;



SDL_Texture* press_start_text_texture;
SDL_Texture* new_game_text_texture;
SDL_Texture* load_game_text_texture;
SDL_Texture* how_to_play_text_texture;


SDL_FRect text1Rect;
SDL_FRect text2Rect;
SDL_FRect text3Rect;
SDL_FRect text4Rect;




// I THINK you cannot do this before SDL initializes?
// I wanted to do this on demo.h but maybe that would have been too untidy...
void define_text_locations(){
    /*
    SDL_FRect text1Rect {
        .x = (WINDOW_WIDTH / 2.0f) - (TEXT_WIDTH / 2.0f),     // Centers the text... I hope ":3
        .y = 0.0f,
        .w = TEXT_WIDTH,
        .h = WINDOW_HEIGHT / 8.0f
    };
    */

    text1Rect.x = (WINDOW_WIDTH / 2.0f) - (TEXT_WIDTH / 2.0f);     // Centers the text... I hope ":3
    text1Rect.y = 0.0f;
    text1Rect.w = TEXT_WIDTH;
    text1Rect.h = WINDOW_HEIGHT / 8.0f;


    text2Rect = text1Rect;
    text2Rect.y += LINE_SPACING;

    text3Rect = text2Rect;
    text3Rect.y += LINE_SPACING;

    text4Rect = text3Rect;
    text4Rect.y += LINE_SPACING;
}


static void init_text() {


    // Initialize SDL_TTF.

    if(!TTF_Init()){
        assert(0 && "ERROR: SDL_TTF could not initialize :c");
    }

    mFont = TTF_OpenFont("./Fonts/Minecraft.ttf", 12.0);
    // mFont = TTF_OpenFont("../../Assets/Fonts/Minecraft.ttf", 12.0);


    if(mFont == nullptr){
        assert(0 && "ERROR: Font file \"Minecraft.ttf\" not found :c");
    }

    /*
    supermotor::text::Text   press_start_text           (mRenderer, mFont, "PRESS   START");
    supermotor::text::Text   new_game_text              (mRenderer, mFont, "New Game");
    supermotor::text::Text   load_game_text             (mRenderer, mFont, "Load Game");
    supermotor::text::Text   how_to_play_text           (mRenderer, mFont, "How to Play");
    */

    // press_start_text_texture      = supermotor::text::text_fun(mRenderer, mFont, "PRESS   START");
    // new_game_text_texture         = supermotor::text::text_fun(mRenderer, mFont, "New Game");
    // load_game_text_texture        = supermotor::text::text_fun(mRenderer, mFont, "Load Game");
    // how_to_play_text_texture      = supermotor::text::text_fun(mRenderer, mFont, "How to Play");

    std::string my_texts[4] = {"PRESS   START", "New Game", "Load Game", "How to Play"};
    my_text_textures = supermotor::text::make_texts(mRenderer, my_texts, 4);



    SDL_Log("ERROR: %s", SDL_GetError());

}



struct SDL_Application{

    SDL_Window* mWindow;
    
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

            init_text();
	    }
    }
	// Destructor
	~SDL_Application(){
        TTF_Quit();
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


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0x77, 0x55, 0x77, 0xFF);
		SDL_RenderClear(mRenderer);

        

        // do bulk...        
		// SDL_RenderTexture(mRenderer, press_start_text_texture, nullptr, &text1Rect);
		// SDL_RenderTexture(mRenderer, new_game_text_texture,    nullptr, &text2Rect);
		// SDL_RenderTexture(mRenderer, load_game_text_texture,   nullptr, &text3Rect);
		// SDL_RenderTexture(mRenderer, how_to_play_text_texture, nullptr, &text4Rect);


        // SDL_Log("sizeof vector: %ld", sizeof(my_texts));

        int number_of_texts = my_text_textures.size();
        for (int i = 0; i < number_of_texts; i++){
            
            SDL_Texture* current_texture = my_text_textures.back();

            SDL_Log("#%d: %s", i, "OK");
    
            if (current_texture == nullptr){
                SDL_Log("#%d: %s", i, "NOT OK");
            }

    		SDL_RenderTexture(mRenderer, current_texture, nullptr, &text2Rect);
            my_text_textures.pop_back();

        }
        

		// draw other things here ...

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

        define_text_locations();

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

