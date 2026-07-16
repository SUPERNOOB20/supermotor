#ifndef ANIMATE_HEADER_FILE
#define ANIMATE_HEADER_FILE


// Basic animations for backgrounds and the like.

#include <SDL3/SDL.h>
#include "atlas.h"



// Limitation: Probably only one loop at a time cuz static.
// Will fix in the future with classes and instantiation e.e
void animation_loop(const char direction, SDL_Surface image_surface, SDL_FRect* &image_pos_rect, const char* filename, Uint64 deltaTime) {

    SDL_Texture* = mTexture;        // Texture declaration.

    static frame_counter = 0;
    if (frame_counter = 0) {        // This step is "heavy". We should do this only once. And ideally in a "loading" screen (not in the middle of the gameplay, where it might stutter the game and tamper the player's experience)
        mTexture = generate_and_load_atlas(direction, image_surface, filename);     // Texture initialization (we move your image from the CPU to the GPU here).
    }

    if (direction == vertical){
        SDL_FRect->y += (deltaTime / 100)
    } else {        // direction == horizontal
        SDL_FRect->x += (deltaTime / 100)
    }
    
}




// Only horizontal and vertical animations at the moment.
// Will include diagonal animations in the future (diagonal atlas).
// Might include angles in the future (for animations that don't loop),
// but I have other features as a priority right now,
// cut me some slack...
//
// Direction can be:
// FOR VERTICAL ANIMATIONS:
// down
// up
// FOR HORIZONTAL ANIMATIONS:
// left
// right
// FOR DIAGONAL ANIMATIONS:
// downleft
// downright
// upleft
// upright
//
// I wonder if int could be replaced by something like Uint32 or uint32_t here...
// (e.g: It wouldn't make sense to have an image with negative resolution...)
static void animate(SDL_Renderer mRenderer, const char* direction, Uint64 duration, int texture_height, int texture_width, Uint64 deltaTime){

    if texture_width == nullptr{
        animate_vertically();
    } else if texture_height == nullptr {
        animate_horizontally();
    } // else {
        // animate_diagonally();
    // }
}





#endif
