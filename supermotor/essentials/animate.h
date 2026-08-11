#ifndef ANIMATE_HEADER_FILE
#define ANIMATE_HEADER_FILE


// Basic animations for backgrounds and the like.


#include <tuple>

#include "atlas.h"


enum Animation_Type {
    SIMPLE,     // 0
    ADVANCED   // 1
};







// Same as moving rect.x and rect.y, but more comfortable to me since
// it allows me to move rects with just 1 line of code instead of 2.
SDL_FRect move (SDL_FRect rect, int a, int b){
    rect.x += a;
    rect.y += b;
    return rect;
}







// Limitation: Probably only one loop at a time cuz static.
// Will fix in the future with classes and instantiation e.e


// TODO: Change this to an array...
typedef std::array<std::tuple<SDL_Texture*, SDL_FRect*>, 3> simple_textures_and_locations;
typedef std::array<std::tuple<SDL_Texture*, SDL_FRect*>, 9> advanced_textures_and_locations;




// WIP
// textures_and_locations animation_loop(std::string direction, SDL_Surface* image_surface, SDL_FRect* image_pos_rect, std::string filename, Uint64 deltaTime) {





SDL_FRect image_pos_rect;
SDL_FRect image_2_pos_rect;
SDL_FRect image_3_pos_rect;
SDL_FRect image_4_pos_rect;
SDL_FRect image_5_pos_rect;
SDL_FRect image_6_pos_rect;
SDL_FRect image_7_pos_rect;
SDL_FRect image_8_pos_rect;


SDL_Texture* mTexture;         // Texture declaration.
SDL_Texture* mTexture2;        // Texture declaration.
SDL_Texture* mTexture3;        // Texture declaration.
SDL_Texture* mTexture4;        // Texture declaration.


// simple_animation_loop: Will map a 3-tiled atlas, allowing you to move only up, down, left, or right.
//
// duration and deltaTime are in milliseconds (you can change it to any other unit of time if needed, though).
simple_textures_and_locations simple_animation_loop(SDL_Renderer* mRenderer, Uint64 duration, float width, float height, unsigned short int atlas_direction, SDL_Surface* image_surface, std::string filename, Uint64 deltaTime) {       // Again... float width and height to match SDL's float qwq

    image_pos_rect.x = 0.0f;
    image_pos_rect.y = 0.0f;
    image_pos_rect.w = width;
    image_pos_rect.h = height;
    
    image_2_pos_rect = image_pos_rect;
    image_3_pos_rect = image_pos_rect;
    image_4_pos_rect = image_pos_rect;
    image_5_pos_rect = image_pos_rect;
    image_6_pos_rect = image_pos_rect;
    image_7_pos_rect = image_pos_rect;
    image_8_pos_rect = image_pos_rect;



    int texture_width;        //  "int" because I believe SDL saves texture_width  as int (as opposed to unsigned int...)
    int texture_height;      //   "int" because I believe SDL saves texture_height as int (as opposed to unsigned int...)


    static bool frame_counter = 0;
    if (frame_counter = 0) {        // This step is "heavy". We should do this only once. And ideally in a "loading" screen (not in the middle of the gameplay, where it might stutter the game and tamper the player's experience)


        atlas my_atlas = generate_and_load_atlas(mRenderer, atlas_direction, image_surface, filename);

        // mTexture    = std::get<0>(my_atlas);     // Texture initialization (we move your image from the CPU to the GPU here).
        // mTexture2   = std::get<1>(my_atlas);     // Texture initialization (we move your image from the CPU to the GPU here).

        mTexture       = my_atlas[0];               // Texture initialization (we move your image from the CPU to the GPU here).
        mTexture2      = my_atlas[1];               // Texture initialization (we move your image from the CPU to the GPU here).

        
        texture_width  = mTexture->w;
        texture_height = mTexture->h;

        
        switch (direction){


            case 1:
                image_2_pos_rect.y = image_pos_rect.y +     image_pos_rect.h;   // Case UP
                image_3_pos_rect.y = image_pos_rect.y + 2 * image_pos_rect.h;
            break;

            case 3:
                image_2_pos_rect.x = image_pos_rect.x +     image_pos_rect.w;   // Case RIGHT
                image_3_pos_rect.y = image_pos_rect.x + 2 * image_pos_rect.h;
            break;

            case 5:
                image_2_pos_rect.y = image_pos_rect.y -     image_pos_rect.h;   // Case DOWN
                image_3_pos_rect.y = image_pos_rect.y - 2 * image_pos_rect.h;
            break;

            case 7:
                image_2_pos_rect.x = image_pos_rect.x -     image_pos_rect.w;   // Case LEFT
                image_3_pos_rect.y = image_pos_rect.x - 2 * image_pos_rect.h;
            break;

        }

        */
    }

    frame_counter += 1;

    
    switch (direction){
        
        case 1: // Case UP
        image_pos_rect.y     -= (deltaTime / duration);
        image_2_pos_rect.y   -= (deltaTime / duration);
        image_3_pos_rect.y   -= (deltaTime / duration);        

        case 3: // Case RIGHT
        image_pos_rect.x   += (deltaTime / duration);
        image_2_pos_rect.x += (deltaTime / duration);
        image_3_pos_rect.x += (deltaTime / duration);

        case 5: // Case DOWN
        image_pos_rect.y   += (deltaTime / duration);
        image_2_pos_rect.y += (deltaTime / duration);
        image_3_pos_rect.y += (deltaTime / duration);

        case 7: // Case LEFT
        image_pos_rect.x   -= (deltaTime / duration);
        image_2_pos_rect.x -= (deltaTime / duration);
        image_3_pos_rect.x -= (deltaTime / duration);
    }
    



    std::tuple<SDL_Texture*, SDL_FRect*> image1(
        mTexture,
        &image_pos_rect
    );

    std::tuple<SDL_Texture*, SDL_FRect*> image2(
        mTexture2,
        &image_2_pos_rect
    );

    std::tuple<SDL_Texture*, SDL_FRect*> image3(
        mTexture,
        &image_3_pos_rect
    );

    simple_textures_and_locations my_textures_and_locations {image1, image2, image3};       // Array initialization.

    return my_textures_and_locations;
}



// For simple animations, just omit the last two parameters (https://cplusplus.com/forum/general/69189/#msg369397)
void render_animation(bool animation_type, SDL_Renderer* mRenderer, Uint64 duration, float width, float height, unsigned short int atlas_direction, SDL_Surface* image_surface, Uint64 deltaTime, std::string filename1, std::string filename2, std::string filename3){
    if (animation_type == 0){
        simple_animation_loop(mRenderer, duration, width, height, atlas_direction, image_surface, deltaTime, filename1);
    } else {
        advanced_animation_loop(mRenderer, duration, width, height, atlas_direction, image_surface, deltaTime, filename1, filename2, filename3);
    }
}


// ----------------------------------------------------------------------
//          Stop reading here (?
// ----------------------------------------------------------------------


/*

switch(direction){

    case 0:
        image_2_pos_rect.y = image_pos_rect.y - image_pos_rect.h;       // Case UP_LEFT
        image_3_pos_rect.y = image_pos_rect.y - 2 * image_pos_rect.h;
    break;


}


// advanced_animation_loop: Will map a 9-tiled atlas, allowing you to move in all directions (diagonals and curves).
//
// duration and deltaTime are in milliseconds (you can change it to any other unit of time if needed, though).
textures_and_locations advanced_animation_loop(SDL_Renderer* mRenderer, Uint64 duration, float width, float height, unsigned short int atlas_direction, SDL_Surface* image_surface, std::string filename, Uint64 deltaTime) {       // Again... float width and height to match SDL's float qwq
    
}

*/

#endif
