#ifndef PLATFORMING_HEADER_FILE
#define PLATFORMING_HEADER_FILE


#include "../../supermotor/essentials/collisions.h"
#include "../../supermotor/essentials/common.h"






//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Adjust these to your liking! :3
int floaty_jump_intensity = 10;            // The bigger, the longer you can hold the jump button for. Change to 0 if you want the player to always jump at the same height!
float gravity = 1.0f;                     //  The bigger, the smaller your jumps.
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//  ----------------  PLAYER  ----------------------------------------------------------------------------------------------------------------------------------
//  Your player's texture resolution goes here.
// int player_texture_width = 32;
// int player_texture_height = 32;

#ifndef player_texture_width
    #define player_texture_width 32
#endif

#ifndef player_texture_height
    #define player_texture_height 32
#endif

/*
void set_player_size(int width, int height) {
    player_texture_width = width;
    player_texture_height = height;
}
*/



SDL_FRect Player{
    .x = ((float) WINDOW_WIDTH)  / 2.0f,
    .y = ((float) WINDOW_HEIGHT)  / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};
//  ------------------------------------------------------------------------------------------------------------------------------------------------------------







//  ----------- Collisions and physics ---------

// std::array<int, 2> previous_player_pos = {0, 0};
// std::array<int, 2> current_player_pos = {0, 0};

SDL_FRect Dummy_previous_player_pos{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};
supermotor::Rect Previous_player_pos(Dummy_previous_player_pos);


SDL_FRect Dummy_current_player_pos{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};
supermotor::Rect Current_player_pos(Dummy_current_player_pos);



// Function declaration.
// vertical_velocity_decay();
// update_player_pos();
// is_airborne();



std::vector<SDL_FRect> your_obstacles_here;        // I want global obstacles so I don't have to send them as parameters everywhere.
// your_obstacles_here.reserve(6);                 // We may not be able to add the obstacles to our vector before SDL_Application, but we can at least reserve beforehand... right? right....? Ah, I guess not... well, dammit! heh ":3




static Uint64 frame = 0;

static int jumping_frame_limit = floaty_jump_intensity;

static int frames_since_started_jumping = -1;
static bool player_just_jumped = (frames_since_started_jumping != -1);

bool is_airborne = false;       // (!is_airborne) means is_on_the_ground.

static bool player_can_jump = (frames_since_started_jumping >= 0) && (!is_airborne);



const bool* keyboardState = SDL_GetKeyboardState(nullptr);   // Reminder for self: We use NULL in C, and we use nullptr in C++


void update_jump_status(){
    // jumping_frame_limit = floaty_jump_intensity;     // Uncommentate if your game varies floaty jump intensities on runtime.

    player_just_jumped = (frames_since_started_jumping != -1);

    player_can_jump = (frames_since_started_jumping != -1) || (!is_airborne);
}






void reset_vertical_timer(){
    
    if (player_just_jumped){
        frames_since_started_jumping++;
    }

    if (frames_since_started_jumping > floaty_jump_intensity){
        frames_since_started_jumping = -1;      // Now you can't hold your jump button forever and fly away anymore *chuckles*.
    }
}


void reset_jump(){
    if (!is_airborne){
        frames_since_started_jumping = 0;       // You will always be able to jump if you're on the ground.
    }
}



bool player_is_on_the_ground(supermotor::Rect current_obstacle){

    bool res = false;

    supermotor::Rect dummy_current_obstacle(current_obstacle);
    dummy_current_obstacle.move_y(-2);  // Remember that our origin (0, 0) is the top-left corner of the screen.

    if (((supermotor::collidingVertices(Player, current_obstacle)).size() == 0) && (supermotor::collidingVertices(Player, dummy_current_obstacle).size() > 0)) {
        res = true;
    }    

    return res;
}


// consumes     std::vector<SDL_FRect> your_obstacles_here
// and          std::array <int, 2> current_player_pos = {0, 0};
//
// Should be pretty self explanatory:
// If there are no current collisions, then the player is airborne.
bool check_airborne(){

    bool res = true;
    
    Uint32 your_obstacles_amount = your_obstacles_here.size();

    for (int i = 0; i < your_obstacles_amount; i++){

        supermotor::Rect current_obstacle = your_obstacles_here[i];

        if (player_is_on_the_ground(current_obstacle)) {       // your_obstacles_here[i] is the current_obstacle.
            // SDL_Log("is airborne: false");
            res = false;
        }
    }

    return res;
}


void vertical_velocity_decay() {
    if (is_airborne){
        vertical_velocity += gravity;
    } else {
        vertical_velocity = 0.0f;
    }
}




// See https://wiki.libsdl.org/SDL3/BestKeyboardPractices and https://wiki.libsdl.org/SDL3/SDL_Scancode
void process_vertical_movement(){


    // Up arrow key.
    if (keyboardState[SDL_SCANCODE_UP]) {   
        if (player_can_jump){
		    // Player jumps :3
		    vertical_velocity = -10.0f;
            frames_since_started_jumping++;
        }
    }
}






void process_horizontal_movement(){


    // Left arrow key.
    if (keyboardState[SDL_SCANCODE_LEFT]) {
		// Player moves to the left :3
		horizontal_velocity -= 3.0f;
        if (keyboardState[SDL_SCANCODE_D]) {
            horizontal_velocity -= 6.0f;
        }
    }


    // Right arrow key.
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
       	// Player moves to the right :3
		horizontal_velocity += 3.0f;
        if (keyboardState[SDL_SCANCODE_D]) {
            horizontal_velocity += 6.0f;
        }
	}
}













void update_player_pos() {

    // Stores player pos from the previous frame (for collision handling purposes).
    Previous_player_pos = Current_player_pos;        // Previous_player_pos <--- Current_player_pos




    // From here on... Current_player_pos <--- New_player_pos

    process_vertical_movement();
    process_horizontal_movement();

    Current_player_pos.move_x(horizontal_velocity);
    Current_player_pos.move_y(vertical_velocity);

    horizontal_velocity = 0;
    // vertical_velocity = 0;

    vertical_velocity_decay();      // You can refactor this to use "float gravity" or "double gravity" as a parameter here if you want.

    Current_player_pos = supermotor::handle_collisions(Previous_player_pos, Current_player_pos, your_obstacles_here);

    Player = supermotor::convert_supermotor_rect_to_sdl_rect(Current_player_pos, Player);
}


// -------------------------------------------



#endif
