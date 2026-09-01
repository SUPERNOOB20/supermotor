#ifndef PLATFORMER_EXAMPLE_3_HEADER_FILE
#define PLATFORMER_EXAMPLE_3_HEADER_FILE



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


#include "../../../supermotor/essentials/platforming.h"




// Your player's texture resolution goes here.
int player_texture_width = 45;
int player_texture_height = 98;


SDL_FRect Player{
    .x = ((float) WINDOW_WIDTH)  / 2.0f,
    .y = ((float) WINDOW_HEIGHT)  / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};


SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT
};


SDL_FRect ObstacleFloor1{
    .x = 0,
    .y = WINDOW_HEIGHT  / 1.4f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 2
};


SDL_FRect ObstacleIce1{
    .x = WINDOW_WIDTH  / 3.95f,
    .y = WINDOW_HEIGHT  / 1.4f,
    .w = WINDOW_WIDTH  / 2.0f,
    .h = WINDOW_HEIGHT / 5.0f
};



SDL_FRect ObstacleWall1{
    .x = 0,
    .y = WINDOW_HEIGHT  / 3.0f,
    .w = WINDOW_WIDTH / 10.0f,
    .h = WINDOW_HEIGHT
};


SDL_FRect ObstacleWall2{
    .x = WINDOW_WIDTH / 1.1f,
    .y = WINDOW_HEIGHT  / 3.0f,
    .w = WINDOW_WIDTH / 10.0f,
    .h = WINDOW_HEIGHT
};





#endif
