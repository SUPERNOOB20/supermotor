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




bool generate_horizontal_atlas(SDL_Surface* image_surface, const char* filename){

    bool success;
    success = SDL_FlipSurface(image_surface, SDL_FLIP_HORIZONTAL);
    if (!success){
        return 1;   // We tried to flip your image, but we failed :c
    }
    

    !SDL_SavePNG(image_surface, filename);

    return 0;   // Success! :3
}t




bool generate_vertical_atlas(SDL_Surface* image_surface, const char* filename){

    bool success;
    success = SDL_FlipSurface(image_surface, SDL_FLIP_VERTICAL);
    if (!success){
        return 1;   // We tried to flip your image, but we failed :c
    }
    

    !SDL_SavePNG(image_surface, filename);

    return 0;   // Success! :3
}


SDL_Texture load_atlas(SDL_Renderer* mRenderer, SDL_Surface* image_surface){

    SDL_Texture* mTexture
    bgTexture = SDL_CreateTextureFromSurface(mRenderer, image_surface);

    return mTexture;   // Success! :3
}




SDL_Texture generate_and_load_atlas(SDL_Renderer* mRenderer, const char* direction, SDL_Surface* image_surface, const char* filename){

    if direction == vertical{
        generate_vertical_atlas(image_surface, filename);    
    } else {       // direction == horizontal
        generate_horizontal_atlas(image_surface, filename);    
    }
    

    load_atlas(mRenderer, image_surface);

    return mTexture;   // Success! :3
}

#endif
