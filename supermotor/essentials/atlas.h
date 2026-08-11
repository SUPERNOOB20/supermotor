#ifndef ATLAS_HEADER_FILE
#define ATLAS_HEADER_FILE


// Animation atlas.
// These functions are handled by the CPU
// and are rather costly - my suggestions is that you
// use them only once, at the very start of your game
// (when loading your various assets)
// or before the game even starts
//
// (do NOT run these functions
//  every single frame of your game!!!)




#include <string>

#include <array>
#include <vector>

#include <SDL3/SDL.h>


// By design, it spins clockwise.
// You can change the order if you don't find it comfortable.
// Check the adjointed image "visual_explanations/explanation_1_direction.png" for an explanation.
enum Orientation {
    UP_LEFT,     // 0
    UP,          // 1
    UP_RIGHT,    // 2
    RIGHT,       // 3
    DOWN_RIGHT,  // 4
    DOWN,        // 5
    DOWN_LEFT,   // 6
    LEFT         // 7
};



enum Direction {
    VERTICAL,     // 0
    HORIZONTAL,   // 1
    DIAGONAL      // 2
};







// Simple (vertical / horizontal)  atlas require 2 textures (the original one, and the flipped one (either x-axis-flipped or y-axis-flipped)).
// Advanced (diagonals and curves) atlas require 4 textures (the original one, the x-axis flipped one, the y-axis flipped one, and the xy-axis flipped one).

// Simple (vertical / horizontal)  atlas require 3 rects (rendering the same image "3 times", in 3 different places).
// Advanced (diagonals and curves) atlas require 9 rects (rendering the same image "9 times", in 9 different places).


typedef std::array<SDL_Texture*, 2> simple_atlas;             // 2 rects: Original, and flipped. 
typedef std::array<SDL_Texture*, 4> advanced_atlas;          //  3 rects: Original, flipped x-axis, flipped y-axis, flipped xy-axis.







// Horizontal and vertical loop animations require 2 textures:
// texture1: Original one
// texture2: Flipped one
// If I ever implement diagonal atlases, there will be 8 textures... yeah, that will definitely require a lot of refactoring e.e
simple_atlas generate_and_load_simple_atlas(SDL_Renderer* mRenderer, unsigned short int atlas_direction, SDL_Surface* image_surface, std::string filename){

    SDL_Surface* flipped_surface = image_surface;

    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(mRenderer, image_surface);

    if ((atlas_direction == UP) || (atlas_direction == DOWN)) {

        SDL_FlipSurface(flipped_surface, SDL_FLIP_VERTICAL);

    } else {        // ((atlas_direction == LEFT) || (atlas_direction == RIGHT))

        SDL_FlipSurface(flipped_surface, SDL_FLIP_HORIZONTAL);
        
    }

    SDL_SavePNG(flipped_surface, filename.c_str());

    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(mRenderer, flipped_surface);

    simple_atlas my_atlas = {texture1, texture2};

    return my_atlas;   // Success! :3
}


advanced_atlas generate_and_load_simple_atlas(SDL_Renderer* mRenderer, unsigned short int atlas_direction, SDL_Surface* image_surface, std::string filename1, std::string filename2, std::string filename3){

    SDL_Surface* flipped_x_surface  = image_surface;
    SDL_Surface* flipped_y_surface  = image_surface;
    SDL_Surface* flipped_xy_surface;

    SDL_FlipSurface(flipped_x_surface, SDL_FLIP_HORIZONTAL);
    SDL_Surface* flipped_xy_surface = flipped_x_surface;
    SDL_FlipSurface(flipped_y_surface, SDL_FLIP_VERTICAL);
    SDL_FlipSurface(flipped_xy_surface, SDL_FLIP_VERTICAL);

    
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(mRenderer, image_surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(mRenderer, flipped_x_surface);
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(mRenderer, flipped_y_surface);
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(mRenderer, flipped_xy_surface);

    advanced_atlas my_atlas = {texture1, texture2, texture3, texture4};

    return my_atlas;   // Success! :3
}


#endif
