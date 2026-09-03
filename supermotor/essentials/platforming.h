#ifndef PLATFORMING_HEADER_FILE
#define PLATFORMING_HEADER_FILE


#include "../../supermotor/essentials/collisions.h"
#include "../../supermotor/essentials/common.h"


namespace supermotor
{


namespace platforming
{





//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  Adjust these to your liking! :3
int floaty_jump_intensity = 10;            // The bigger, the longer you can hold the jump button for. Change to 0 if you want the player to always jump at the same height!
float gravity = 1.0f;                     //  The bigger, the smaller your jumps.
float ice_speed = 2.5f;                  //   The player's speed will be multiplied by this number when standing on ice.
//  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//  ----------------  PLAYER  ----------------------------------------------------------------------------------------------------------------------------------
//  Your player's texture resolution goes here.
int player_texture_width = 32;
int player_texture_height = 32;



// Visuals.
SDL_FRect PlayerTexture{
    .x = ((float) WINDOW_WIDTH)  / 2.0f,
    .y = ((float) WINDOW_HEIGHT) / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};


// Hurtbox to take damage from hazards.
SDL_FRect PlayerHurtbox{
    .x = ((float) WINDOW_WIDTH)  / 2.0f,
    .y = ((float) WINDOW_HEIGHT) / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};


// Hitbox for collisions with obstacles (you know, the platforming physics).
SDL_FRect Player{
    .x = ((float) WINDOW_WIDTH)  / 2.0f,
    .y = ((float) WINDOW_HEIGHT) / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};
//  ------------------------------------------------------------------------------------------------------------------------------------------------------------










//  ----------- Collisions and physics ---------


// In my mind, it looked like this:
// std::array<int, 2> previous_player_pos = {0, 0};
// std::array<int, 2> current_player_pos = {0, 0};


// Initial player position.
SDL_FRect Dummy_previous_player_pos{
    .x = WINDOW_WIDTH  / 2.0f,
    .y = WINDOW_HEIGHT  / 2.7f,
    .w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)),          // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    .h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height))
};
supermotor::Rect Previous_player_pos(Dummy_previous_player_pos);
supermotor::Rect  Current_player_pos(Dummy_previous_player_pos);



// Warning #1: Might reset some stuff
// Warning #2: I have no idea what I'm doing
//
void set_player_size(int width, int height) {
    
    // Global change.
    player_texture_width = width;
    player_texture_height = height;


    // Specific changes.
    Player.w = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width));                                                  // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    Player.h = ((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height));


    
    Current_player_pos.set_width    (((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)));               //  WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    Current_player_pos.set_height   (((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height)));              //   WINDOW_WIDTH / WINDOW_HEIGHT = ratio

    Previous_player_pos.set_width   (((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_width)));            //    WINDOW_WIDTH / WINDOW_HEIGHT = ratio        // WINDOW_WIDTH / WINDOW_HEIGHT = ratio
    Previous_player_pos.set_height  (((float) (WINDOW_WIDTH) / (float) (WINDOW_HEIGHT)) * ((float) (player_texture_height)));           //     WINDOW_WIDTH / WINDOW_HEIGHT = ratio
}







// I want global obstacles so I don't have to send them as parameters everywhere.
std::vector<SDL_FRect>          your_obstacles_here                 {{}};

std::vector<SDL_FRect>          your_1d_up_obstacles_here           {{}};
std::vector<SDL_FRect>          your_1d_down_obstacles_here         {{}};

std::vector<SDL_FRect>          your_floor_obstacles_here           {{}};

std::vector<SDL_FRect>          your_ice_obstacles_here             {{}};
std::vector<MovingPlatform>     your_moving_platforms_here          {{}};








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



bool player_is_on_the_ground(supermotor::Rect current_obstacle, bool check_for_ice){

    bool res = false;
    bool standing_on_ice = false;

    supermotor::Rect dummy_current_obstacle(current_obstacle);
    dummy_current_obstacle.move_y(-2);  // Remember that our origin (0, 0) is the top-left corner of the screen.

    if (((supermotor::collidingVertices(Player, current_obstacle)).size() == 0) && (supermotor::collidingVertices(Player, dummy_current_obstacle).size() > 0)) {
        res = true;
        standing_on_ice = true;
    }    

    if(check_for_ice && standing_on_ice) { horizontal_velocity *= ice_speed; } 

    return res;
}



// consumes     std::vector<SDL_FRect> your_obstacles_here
// and          std::array <int, 2> current_player_pos = {0, 0};
//
// Should be pretty self explanatory:
// If there are no current collisions, then the player is airborne.
bool check_airborne(){

    bool res = true;    

    for (auto &current_obstacle : your_obstacles_here) {

        if (player_is_on_the_ground(current_obstacle)) {
            // SDL_Log("is airborne: false");
            res = false;
        }
    }



   for (auto &currentplatform : your_moving_platforms_here) {

        if (player_is_on_the_ground(current_platform)) {
            // SDL_Log("is airborne: false");
            res = false;
        }
    }

    return res;
}



// Apply slippery ice effect if player is above ice.
void check_airborne_ice() {
    Uint32 your_ice_obstacles_amount = your_ice_obstacles_here.size();

    for (int i = 0; i < your_ice_obstacles_amount; i++){

        supermotor::Rect current_ice_obstacle = your_ice_obstacles_here[i];

        player_is_on_the_ground(current_ice_obstacle, true);
    }
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

    check_airborne_ice();

    Current_player_pos.move_x(horizontal_velocity);
    Current_player_pos.move_y(vertical_velocity);

    horizontal_velocity = 0;
    // vertical_velocity = 0;

    vertical_velocity_decay();      // You can refactor this to use "float gravity" or "double gravity" as a parameter here if you want.

    Current_player_pos = supermotor::handle_collisions(Previous_player_pos, Current_player_pos, your_obstacles_here);

    Player = supermotor::convert_supermotor_rect_to_sdl_rect(Current_player_pos, Player);
}




void update_platforms() {

    /*    
    for (MovingPlatform current_platform : your_moving_platforms_here)
        current_platform.UpdatePosition(frame);
    */


    for (auto& current_platform : your_moving_platforms_here)
        current_platform.UpdatePosition(frame);
}







// -------------------------------------------
// Utilities:

// Call this function every frame for your platforming to update properly!
// (Should be called in the Update() part.)
// (That is: AFTER the player inputs are processed, but BEFORE anything gets rendered on screen).
//
//
void update_platforming_state() {



    update_platforms();



    is_airborne = check_airborne();

    update_player_pos();

    reset_vertical_timer();

    update_jump_status();

    reset_jump();
}


// -------------------------------------------





}
}

#endif
