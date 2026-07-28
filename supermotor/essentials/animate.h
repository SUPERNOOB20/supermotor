#ifndef ANIMATE_HEADER_FILE
#define ANIMATE_HEADER_FILE


// Basic animations for backgrounds and the like.


#include <tuple>

#include "atlas.h"




// Limitation: Probably only one loop at a time cuz static.
// Will fix in the future with classes and instantiation e.e
// std::array[SDL_Texture] animation_loop(std::string direction, SDL_Surface* image_surface, SDL_FRect* &image_pos_rect, std::string filename, Uint64 deltaTime) {


typedef std::vector<std::tuple<SDL_Texture*, SDL_FRect*>> textures_and_locations;


// WIP
// textures_and_locations animation_loop(std::string direction, SDL_Surface* image_surface, SDL_FRect* image_pos_rect, std::string filename, Uint64 deltaTime) {





SDL_FRect image_pos_rect;
SDL_FRect image_2_pos_rect;

SDL_Texture* mTexture;         // Texture declaration.
SDL_Texture* mTexture2;        // Texture declaration.


textures_and_locations animation_loop(SDL_Renderer* mRenderer, float width, float height, std::string direction, SDL_Surface* image_surface, std::string filename, Uint64 deltaTime) {       // Again... float width and height to match SDL's float qwq

    image_pos_rect.x = 0.0f;
    image_pos_rect.y = 0.0f;
    image_pos_rect.w = width;
    image_pos_rect.h = height;
    
    image_2_pos_rect = image_pos_rect;



    int texture_width;        //  "int" because I believe SDL saves texture_width  as int (as opposed to unsigned int...)
    int texture_height;      //   "int" because I believe SDL saves texture_height as int (as opposed to unsigned int...)


    static bool frame_counter = 0;
    if (frame_counter = 0) {        // This step is "heavy". We should do this only once. And ideally in a "loading" screen (not in the middle of the gameplay, where it might stutter the game and tamper the player's experience)


        atlas my_atlas = generate_and_load_atlas(mRenderer, direction, image_surface, filename);

        // mTexture    = std::get<0>(my_atlas);     // Texture initialization (we move your image from the CPU to the GPU here).
        // mTexture2   = std::get<1>(my_atlas);     // Texture initialization (we move your image from the CPU to the GPU here).

        mTexture       = my_atlas[0];               // Texture initialization (we move your image from the CPU to the GPU here).
        mTexture2      = my_atlas[1];               // Texture initialization (we move your image from the CPU to the GPU here).

        
        texture_width  = mTexture->w;
        texture_height = mTexture->h;


        if (direction == "VERTICAL") {

            image_2_pos_rect.y = image_pos_rect.y + image_pos_rect.h;

        } else if (direction == "HORIZONTAL") {

            image_2_pos_rect.x = image_pos_rect.x + image_pos_rect.w;

        }

    }

    frame_counter += 1;

    if (direction == "VERTICAL"){
        image_pos_rect.y   += (deltaTime / 10000);
        image_2_pos_rect.y += (deltaTime / 10000);
    } else if (direction == "HORIZONTAL") {
        image_pos_rect.x += (deltaTime / 10000);
        image_2_pos_rect.x += (deltaTime / 10000);
    }




    std::tuple<SDL_Texture*, SDL_FRect*> image1(
        mTexture,
        &image_pos_rect
    );

    std::tuple<SDL_Texture*, SDL_FRect*> image2(
        mTexture2,
        &image_2_pos_rect
    );

    textures_and_locations my_textures_and_locations;


    my_textures_and_locations.push_back(image1);
    my_textures_and_locations.push_back(image2); 

    return my_textures_and_locations;
}


// ----------------------------------------------------------------------
//          Stop reading here (?
// ----------------------------------------------------------------------








/*

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
static void animate(SDL_Renderer* mRenderer, std::string direction, Uint64 duration, int texture_height, int texture_width, Uint64 deltaTime){

    if (texture_width == nullptr) {
        animate_vertically();
    } else if (texture_height == nullptr) {
        animate_horizontally();
    } // else {
        // animate_diagonally();
    // }
}

*/



#endif
