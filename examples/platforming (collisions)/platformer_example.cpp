// Credits to Mike Shah for the boilerplating  -  https://youtu.be/yZl9X47cHi8
// g++ platformer_example.cpp -O3 -o platformer_demo `pkg-config --libs --cflags sdl3`

// .
// .
// .

#include <SDL3/SDL.h>
#include <string>
#include <cassert>
#include <vector>

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT   720

#define INERTIA 1.0f

std::vector<SDL_Texture*> your_textures_here;
std::vector<SDL_FRect> your_obstacles_here;

double vertical_velocity = 0.0f;
double horizontal_velocity = 0.0f;

// Your player's texture resolution goes here.
int player_texture_height = 45;
int player_texture_width = 98;


SDL_FRect Player{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 10.0f,
    .w = player_texture_width,
    .h = player_texture_height
}


SDL_FRect Obstacle1{
    .x = 0,
    .y = WINDOW_HEIGHT  / 1.15f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 10
}

SDL_FRect Obstacle2{
    .x = WINDOW_WIDTH  / 1.5f,
    .y = WINDOW_WIDTH  / 2.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 10.0f
}

SDL_FRect Obstacle3{
    .x = WINDOW_WIDTH  / 3.5f,
    .y = WINDOW_WIDTH  / 2.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 10.0f
}



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


	    SDL_Surface* player_surface = SDL_LoadPNG("./silly_thing.png");
	    if (player_surface == nullptr){
		    assert(0 && "ERROR: File not found :c");
	    }
        
        playerTexture = SDL_CreateTextureFromSurface(mRenderer, player_surface);
	    your_textures_here.push_back(playerTexture);

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
                    SDL_Quit();
                }

                switch (event.button.button) {

	            	case 79:
	            		// Player moves to the right :3
	            		horizontal_velocity += 0.05f;
	            		break;
	            		
            		case 80:
                       	// Player moves to the left :3
            			horizontal_velocity -= 0.05f;
    			}
            }
		}
	}

   
	void Update(){

        is_airborne(obstacles);

        handle_collisions(previous_player_pos, current_player_pos, obstacles);
        player_pos_x += vertical_velocity;

        if (vertical_velocity < gravity) {
            vertical_velocity = 0.0f;
        } else if (vertical_velocity >= gravity) {
            vertical_velocity -= gravity;
        }
	}


	void Render(){

		SDL_SetRenderDrawColor(mRenderer, 0xBB, 0xAA, 0xEE, 0xFF);
		SDL_RenderClear(mRenderer);

        for (SDL_Texture texture : your_textures_here){
    		SDL_RenderTexture(mRenderer, texture, nullptr, nullptr);
        }

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

