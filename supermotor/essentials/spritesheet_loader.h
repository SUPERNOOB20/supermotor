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
 
    // Similar to supermotor::generate_texture(...), but this one lets you include color key :3
    SDL_Texture* create_spritesheet(SDL_Renderer* mRenderer, std::string filename, Uint8 transparency_colour_red, Uint8 transparency_colour_green, Uint8 transparency_colour_blue){

        SDL_Surface* six_seven;         // SIX SEEEEEEEEEEVEN
        SDL_Texture* your_texture;

        six_seven = SDL_LoadBMP(filename.c_str());     // If you want other fileformats, do the find_file_format thingy from core.h, I'm too lazy to do it myself right now... e.e

        if (six_seven == nullptr){
		    assert(0 && ("ERROR: spritesheet image file not found :c"));
	    }

        const SDL_PixelFormatDetails* surface_details = SDL_GetPixelFormatDetails(six_seven->format);   // Usually BRG or RGB.
        SDL_Palette* surface_palette = SDL_GetSurfacePalette(six_seven);
        Uint32 colorKey = SDL_MapRGB(surface_details, surface_palette, transparency_colour_red, transparency_colour_green, transparency_colour_blue);          // Lets us treat a surface as RGB regardless of internal representation (think of different bpp and different endianess, for example).

        SDL_SetSurfaceColorKey(six_seven, true, colorKey);

        your_texture = SDL_CreateTextureFromSurface(mRenderer, six_seven);
        SDL_DestroySurface(six_seven);

        return your_texture;
    }

   
    // You can once again thank the allmighty Mike Shah for the core idea behind this whole library! Taken from here ---> https://www.youtube.com/watch?v=GpCcQeoYYKE
    //
    // Returns a vector with all your sprites, in order.
    // for the width and height parameters: I recommend you to use nullptr for the one you won't use.
    //
    // That is to say:
    //    sprite_height == nullptr for HORIZONTAL
    //       and
    //    sprite_width == nullptr for VERTICAL
    //
    //
    // Want to optimise this further? Try returning an array instead of a vector! ":3
    //
    // I have also included some small amounts of SDL_Log for you to uncommentate and use when debugging if needed :3
    //    Enjoy! ^- ^)7
    //
    std::vector<SDL_FRect> load_spritesheet(SDL_Texture* spritesheet_texture, unsigned int sprite_height, unsigned int sprite_width, bool direction){

        unsigned int texture_height = spritesheet_texture->h;
        unsigned int texture_width = spritesheet_texture->w;

        std::vector<SDL_FRect> spritesheet_rects; 

        if (direction == HORIZONTAL) {
        
            unsigned int size = texture_width / sprite_width;       // Amount of sprites to generate.  
            spritesheet_rects.resize(size);

            for (int i = 0; i < size; i++){
                SDL_FRect current_sprite {
                    .x = (float) (i * size),
                    .y = 0.0f,
                    .w = (float) (sprite_width),
                    .h = (float) (texture_height)
                };                
                spritesheet_rects[i] = current_sprite;

                /*
                SDL_Log("\n");
                SDL_Log("Current texture: %d", i);
                SDL_Log("Starts at: %f", current_sprite.x);
                SDL_Log("Finished at: %f", current_sprite.x + current_sprite.w);
                */
            }

        } else { // direction == VERTICAL
 
            unsigned int size = texture_height / sprite_height;       // Amount of sprites to generate.
            spritesheet_rects.resize(size);

            for (int i = 0; i < size; i++){
                SDL_FRect current_sprite {
                    .x = 0.0f,
                    .y = (float) (i * sprite_height),
                    .w = (float) (texture_width),
                    .h = (float) (sprite_height)
                };                
                spritesheet_rects[i] = current_sprite;

                /*
                SDL_Log("\n");
                SDL_Log("Current texture: %d", i);
                SDL_Log("Starts at: %f", current_sprite.y);
                SDL_Log("Finished at: %f", current_sprite.y + current_sprite.h);
                */
            }

        }


        return spritesheet_rects;
    }
}


#endif
