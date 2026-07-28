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


typedef std::array<SDL_Texture*, 2> atlas;                  // Fast, but only accepts vertical and horizontal. 
// typedef std::vector<SDL_Texture*> atlas_rework;         //  Accepts diagonal, but marginally slower.





bool generate_atlas(SDL_Surface* image_surface, std::string filename, std::string direction){

    bool success;
    if (direction == "VERTICAL"){
        success = SDL_FlipSurface(image_surface, SDL_FLIP_HORIZONTAL);
    } else if (direction == "HORIZONTAL") {
        success = SDL_FlipSurface(image_surface, SDL_FLIP_VERTICAL);
    }

    if (!success){
        return 1;   // We tried to flip your image, but we failed :c
    }
    

    SDL_SavePNG(image_surface, filename.c_str());

    return 0;   // Success! :3
}


SDL_Texture* load_atlas(SDL_Renderer* mRenderer, SDL_Surface* image_surface){

    SDL_Texture* bgTexture;
    bgTexture = SDL_CreateTextureFromSurface(mRenderer, image_surface);

    return bgTexture;   // Success! :3
}


// Horizontal and vertical loop animations require 2 textures:
// texture1: Original one
// texture2: Flipped one
// If I ever implement diagonal atlases, there will be 8 textures... yeah, that will definitely require a lot of refactoring e.e
atlas generate_and_load_atlas(SDL_Renderer* mRenderer, std::string direction, SDL_Surface* image_surface, std::string filename){

    if (direction == "VERTICAL") {
        generate_atlas(image_surface, filename, "VERTICAL");    
    } else if (direction == "HORIZONTAL") {       // direction == horizontal
        generate_atlas(image_surface, filename, "HORIZONTAL");    
    }
    
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(mRenderer, image_surface);
    SDL_Texture* texture2 = load_atlas(mRenderer, image_surface);

    atlas my_atlas = {texture1, texture2};

    return my_atlas;   // Success! :3
}

#endif
