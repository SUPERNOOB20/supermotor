#ifndef ANCHORS_HEADER_FILE
#define ANCHORS_HEADER_FILE

// Various SDL_FRect utilities like anchors and rescaling :3

#include <SDL3/SDL.h>



namespace supermotor
{

namespace gui
{



// -------  RESCALING  --------------------------------------------------------------------

template <typename T> SDL_FRect resize_rect (SDL_FRect rect, T scalar_factor) {
    rect.x *= scalar_factor;
    rect.y *= scalar_factor;
    rect.w *= scalar_factor;
    rect.h *= scalar_factor;

    return rect;
}




// -------  ANCHORS  ----------------------------------------------------------------------


#define LEFT_SNAP_X     ( rect_B.x )
#define TOP_SNAP_Y      ( rect_B.y )

#define RIGHT_SNAP_X    ( rect_B.x + rect_B.w - rect_A.w )
#define BOTTOM_SNAP_Y   ( rect_B.y + rect_B.h - rect_A.h )


// The idea behind is "C = (Q - P) / 2" (center between two points in 1 dimension)  (where Q is rect_B.x + rect_B.w,  and P is rect_B.x)
// but you also substract half of your inner image to place it's center in that point C :3
//
#define CENTER_SNAP_X   ( rect_B.x + ((rect_B.w - rect_A.w) / 2.0f) )      // Common factor from   (rect_B.x + (rect_B.w / 2.0f) - (rect_A.w / 2.0f))
#define CENTER_SNAP_Y   ( rect_B.y + ((rect_B.h - rect_A.h) / 2.0f) )     //  Common factor from   (rect_B.y + (rect_B.h / 2.0f) - (rect_A.h / 2.0f))


enum Operation {
    TOP_LEFT,       // 0
    TOP,            // 1
    TOP_RIGHT,      // 2
    RIGHT,          // 3
    DOWN_RIGHT,     // 4
    DOWN,           // 5
    DOWN_LEFT,      // 6
    LEFT,           // 7
    CENTER          // 8
};




// Given rectangle A, and rectangle B, places rectangle A relative to rectangle B
// with the specified anchor.
//
// Check out the attached "explanation.png" if you are still confused.
// If you don't understand or want me to make a drawing to explain more easily what this does PLEASE let me know ":3
//
// Oh yeah don't mistake "operation" for "Operation", they are different things, sorry I'm not creative with names okay thanks ":3
//
SDL_FRect anchor (unsigned short int operation, SDL_FRect rect_A, SDL_FRect rect_B) {


       //  -----  Debug utilities :3  ----------------------------------------------------------------------------
      //   SDL_Log("\nrect A: X: %f\n, Y: %f\n, WIDTH: %f\n, HEIGHT: %f\n", rect_A.x, rect_A.y, rect_A.w, rect_A.h);
     //    SDL_Log("\nrect A: X: %f\n, Y: %f\n, WIDTH: %f\n, HEIGHT: %f\n", rect_A.x, rect_A.y, rect_A.w, rect_A.h);
    // -----------------------------------------------------------------------------------------------------------

    switch(operation){

        case TOP_LEFT:
            rect_A.x = LEFT_SNAP_X;
            rect_A.y = TOP_SNAP_Y;
        break;

        case TOP:
            rect_A.x = CENTER_SNAP_X;
            rect_A.y = TOP_SNAP_Y;
        break;

        case TOP_RIGHT:
            rect_A.x = RIGHT_SNAP_X;
            rect_A.y = TOP_SNAP_Y;
        break;

        case RIGHT:
            rect_A.x = RIGHT_SNAP_X;
            rect_A.y = CENTER_SNAP_Y;
        break;

        case DOWN_RIGHT:
            rect_A.x = RIGHT_SNAP_X;
            rect_A.y = BOTTOM_SNAP_Y;
        break;

        case DOWN:
            rect_A.x = CENTER_SNAP_X;
            rect_A.y = BOTTOM_SNAP_Y;
        break;

        case DOWN_LEFT:
            rect_A.x = LEFT_SNAP_X;
            rect_A.y = BOTTOM_SNAP_Y;
        break;
        
        case LEFT:
            rect_A.x = LEFT_SNAP_X;
            rect_A.y = CENTER_SNAP_Y;     // Common factor from   (rect_B.x / 2.0f) - (rect_A.h / 2.0f)
        break;

        case CENTER:
            rect_A.x = CENTER_SNAP_X;
            rect_A.y = CENTER_SNAP_Y;


    }
    return rect_A;
}




/*
SDL_FRect resize_rect (SDL_FRect rect, scalar) {
    
    return ;
}
*/





}
}

#endif
