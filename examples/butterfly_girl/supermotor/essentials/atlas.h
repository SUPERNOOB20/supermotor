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
}




bool generate_vertical_atlas(SDL_Surface* image_surface, const char* filename){

    bool success;
    success = SDL_FlipSurface(image_surface, SDL_FLIP_VERTICAL);
    if (!success){
        return 1;   // We tried to flip your image, but we failed :c
    }
    

    !SDL_SavePNG(image_surface, filename);

    return 0;   // Success! :3
}
