#ifndef PLATFORMER_EXAMPLE_HEADER_FILE
#define PLATFORMER_EXAMPLE_HEADER_FILE



// Usually you use header files to:
// 1) Declare functions (declare function requirements/specification/arity/etc.) (GOOD habit)
// or...
// 2) As a lazy way to have global variables (BAD habit) 
//
// Of course, we are using this header file here for the purposes of 2) :3



#include <SDL3/SDL.h>
#include <string>
#include <cassert>
#include <vector>

#include "../../../supermotor/essentials/collisions.h"
#include "../../../supermotor/essentials/common.h"

#include "../../../supermotor/essentials/platforming.h"




SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT
};


SDL_FRect Obstacle1{
    .x = 0,
    .y = WINDOW_HEIGHT  / 1.4f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 2
};

SDL_FRect Obstacle2{
    .x = WINDOW_WIDTH  / 3.5f,
    .y = WINDOW_HEIGHT  / 5.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 4.0f
};


SDL_FRect Obstacle3{
    .x = WINDOW_WIDTH  / 1.5f,
    .y = WINDOW_HEIGHT  / 1.75f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 5.0f
};


SDL_FRect Obstacle4{
    .x = 0,
    .y = WINDOW_HEIGHT  / 6.0f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 10
};


#endif
