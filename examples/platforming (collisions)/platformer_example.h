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

#include "../../supermotor/essentials/collisions.h"


#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT   720


// #define GRAVITY 1.0f
float gravity = 1.0f;

std::vector<SDL_Texture*> your_textures_here;
std::vector<SDL_FRect> your_obstacles_here;

double vertical_velocity = 0.0f;
double horizontal_velocity = 0.0f;

// Your player's texture resolution goes here.
int player_texture_height = 45;
int player_texture_width = 98;


SDL_FRect Player{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 10.0f,
    .w = (float) player_texture_width,
    .h = (float) player_texture_height
};


SDL_FRect Obstacle1{
    .x = 0,
    .y = WINDOW_HEIGHT  / 1.15f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 10
};

SDL_FRect Obstacle2{
    .x = WINDOW_WIDTH  / 1.5f,
    .y = WINDOW_WIDTH  / 2.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 10.0f
};

SDL_FRect Obstacle3{
    .x = WINDOW_WIDTH  / 3.5f,
    .y = WINDOW_WIDTH  / 2.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 10.0f
};

// std::array<int, 2> previous_player_pos = {0, 0};
// std::array<int, 2> current_player_pos = {0, 0};

SDL_FRect Dummy_previous_player_pos{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 10.0f,
    .w = (float) player_texture_width,
    .h = (float) player_texture_height
};
supermotor::Rect Previous_player_pos(Dummy_previous_player_pos);


SDL_FRect Dummy_current_player_pos{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 10.0f,
    .w = (float) player_texture_width,
    .h = (float) player_texture_height
};
supermotor::Rect Current_player_pos(Dummy_current_player_pos);



// Function declaration.
// vertical_velocity_decay();
// update_player_pos();
// is_airborne();
