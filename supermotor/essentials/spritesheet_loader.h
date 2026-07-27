#ifndef SPRITESHEET_LOADER_HEADER_FILE
#define SPRITESHEET_LOADER_HEADER_FILE

#include "SDL3/SDL.h"
#include <vector>



// WARNING: neither your spritesheet height nor your spritesheet width should exceed 2^16 (65536) pixels.
// This limitation has been placed for the sake of efficiency and common sense.
// Above that value, I cannot guarantee that this library will work properly.
// However, you can change the necessary datatypes if (for whatever MONSTRUOUS reason) you need 2^32 or 2^64.
// ...and as always, if you have any questions, you can always ask me. I'm always happy to help ^_^
//
//          ~ SUPERNOOB20






// Here's hoping this gets stored as a bool value internally... ("^- ^)
enum Direction {
    HORIZONTAL,
    VERTICAL  
};




namespace supermotor
{
    
    // Returns an array with all your sprites, in order.
    // for the width and height parameters: I recommend you to use nullptr for the one you won't use.
    // That is to say:
    //    sprite_height == nullptr for HORIZONTAL
    //       and
    //    sprite_width == nullptr for VERTICAL
    //
    //
    // Want to optimise this further? Try returning an array instead of a vector! ":3
    std::vector<SDL_FRect> load_spritesheet(SDL_Texture* spritesheet_texture, unsigned int sprite_height, unsigned int sprite_width, bool direction){

        unsigned int texture_height = spritesheet_texture->h;
        unsigned int texture_width = spritesheet_texture->w;

        std::vector<SDL_FRect> spritesheet_rects; 

        if (direction == HORIZONTAL) {
        
            unsigned int size = texture_width / sprite_width;       // Amount of sprites to generate.  
            spritesheet_rects.reserve(size);

            for (int i = 0; i < size; i++){
                SDL_FRect current_sprite {
                    .x = (float) (i * size),
                    .y = 0.0f,
                    .w = (float) (sprite_width),
                    .h = (float) (texture_height)
                };                
                spritesheet_rects[i] = current_sprite;
            }

        } else { // direction == VERTICAL
 
            unsigned int size = texture_height / sprite_height;       // Amount of sprites to generate.
            spritesheet_rects.reserve(size);

            for (int i = 0; i < size; i++){
                SDL_FRect current_sprite {
                    .x = 0.0f,
                    .y = (float) (i * size),
                    .w = (float) (texture_width),
                    .h = (float) (sprite_height)
                };                
                spritesheet_rects[i] = current_sprite;
            }

        }

        return spritesheet_rects;
    }
}


#endif
