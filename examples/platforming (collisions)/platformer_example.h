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
    .w = player_texture_width,
    .h = player_texture_height
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

std::array<int, 2> previous_player_pos = {0, 0};
std::array<int, 2> current_player_pos = {0, 0};

void vertical_velocity_decay() {
    if (vertical_velocity < gravity) {
        vertical_velocity = 0.0f;
    } else if (vertical_velocity >= gravity) {
        vertical_velocity -= gravity;
    }
}

void update_player_pos() {

    previous_player_pos = current_player_pos;        // previous_player_pos <--- current_player_pos



    // From here on... current_player_pos <--- new_player_pos

    Player.x += vertical_velocity;

    vertical_velocity_decay();      // You can use "float gravity" or "double gravity" as a parameter here if you want.

    supermotor::handle_collisions(previous_player_pos, current_player_pos, obstacles);
}


// consumes     std::vector<SDL_FRect> your_obstacles_here
// and          std::array <int, 2> current_player_pos = {0, 0};
//
// Should be pretty self explanatory:
// If there is any (currently active) obstacle for which the player would collide
// if the obstacle was one pixel above, then the player is on the ground.
bool is_airborne(){

    bool res = true;

    Uint32 your_obstacles_amount = your_obstacles_here.size();
    for (int i = 0; i < your_obstacles_amount; i++){
        current_obstacle = your_obstacles_here[i];
        dummy_current_obstacle = current_obstacle;
        supermotor::dummy_current_obstacle.move_y(-1);  // Remember that our origin (0, 0) is the top-left corner of the screen.

        if ((supermotor::collidingVertices(Player, current_obstacle).size = 0) && (supermotor::collidingVertices(Player, dummy_current_obstacle).size > 0)){ 
            res = false;
        }
    }

    return False;
}
