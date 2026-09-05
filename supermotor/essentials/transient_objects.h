#ifndef TRANSIENT_OBJECTS_HEADER_FILE
#define TRANSIENT_OBJECTS_HEADER_FILE


#include <SDL3/SDL.h>

#include "collisions.h"
#include "../core.h"           // Even if just for the asset typedef...




namespace supermotor
{



class TransientObject : Rect     // Assuming it inherits private attributes and destructors...
{

  private:
    supermotor::asset attached_asset = nullptr;      // Optional attribute.
    int window_width {1280};     // You will need to update this every frame, or at least whenever you resize your window.
    int window_height {720};    //  You will need to update this every frame, or at least whenever you resize your window.


  public:

    static unsigned long long int ref_count;   // Unless you really really know what you're doing (and you don't), DON'T touch this.


    // Rect + Asset.
    TransientObject(supermotor::asset my_asset, int my_window_width, int my_window_height, Rect* position) : Rect (position) {
        attached_asset = my_asset;
        window_width  = my_window_width;
        window_height = my_window_height;
        
        ref_count++;
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

        if (ref_count > 0) {
            ref_count--;
        } else {
        if ( (attached_asset.texture != nullptr) || (attached_asset.surface != nullptr) )    {
            // SDL_Log("No Objects left!!! Removing asset from RAM...");
            supermotor::destroy_asset(attached_asset);       // If your object has a surface or texture attached to it, free that memory.
            // SDL_Log("Object removed successfully.");
        }
    }
};


void init_transient_objects() {
    unsigned long long int Rect::TransientObject::ref_count = 0;
}




typedef std::vector<SDL_TransientObject>  transient_objects;


// I want global obstacles so I don't have to send them as parameters everywhere.
transient_objects       your_transient_objects_here         {{}};
transient_objects       your_projectiles_here               {{}};


// ^ ... You can keep adding more transient_objects variables if you need to :3




}
#endif
