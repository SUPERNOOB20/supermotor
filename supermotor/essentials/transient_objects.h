#ifndef TRANSIENT_OBJECTS_HEADER_FILE
#define TRANSIENT_OBJECTS_HEADER_FILE

#include "collisions.h"
#include <SDL3/SDL.h>



namespace supermotor
{



class TransientObject : Rect    // Assuming it inherits private attributes and destructors...
{

  private:
    SDL_Texture* attached_texture = nullptr;      // Optional attribute
    int window_width {1280};     // You will need to update this every frame, or at least whenever you resize your window.
    int window_height {720};    //  You will need to update this every frame, or at least whenever you resize your window.

  public:

    // Rect + Texture.
    TransientObject(SDL_Texture* my_texture, int my_window_width, int my_window_height, Rect* position) : Rect (position) {
        attached_texture = my_texture;
        window_width  = my_window_width;
        window_height = my_window_height;
    }


    // Rect.
        TransientObject(int my_window_width, int my_window_height, Rect* position) : Rect (position) {
        window_width  = my_window_width;
        window_height = my_window_height;
    }

    void despawn_check() {

        bool top      =   get_bottom_left_corner_y()    <  0;                 // TransientObject is above the screen
        bool bottom   =   get_top_left_corner_y()       >  window_height;     // TransientObject is below the screen
        bool left     =   get_top_right_corner_x()      <  0;                 // TransientObject is to the left of the screen
        bool right    =   get_top_left_corner_x()       >  window_width;     // TransientObject is to the right of the screen

        bool out_of_bounds = (top || bottom || left || right);

        if (out_of_bounds){
            Despawn();
        }
    }

    // Custom "destructor".
    void Despawn()
    {
        if (attached_texture != nullptr) {
            SDL_DestroyTexture(attached_texture);       // If your object has a texture attached to it, free that memory.
        }
    }
};



typedef std::vector<SDL_TransientObject>  transient_objects;


// I want global obstacles so I don't have to send them as parameters everywhere.
transient_objects       your_transient_objects_here         {{}};
transient_objects       your_projectiles_here               {{}};


// ^ ... You can keep adding more transient_objects variables if you need to :3




}
#endif
