#ifndef DESPAWN_DEMO_HEADER_FILE
#define DESPAWN_DEMO_HEADER_FILE

#include "../../supermotor/essentials/math.h"
#include "../../supermotor/essentials/transient_objects.h"
#include "../../supermotor/essentials/spritesheet_loader.h"

#include <string>
#include <cassert>
#include <vector>

#define WINDOW_WIDTH     1280
#define WINDOW_HEIGHT     720

#define WINDOW_WIDTH_F   1280.0f
#define WINDOW_HEIGHT_F   720.0f

#define PADDING_X (WINDOW_HEIGHT_F/10.0f)
#define PADDING_Y (WINDOW_HEIGHT_F/10.0f)


#define PROJECTILE_SPAWN_RATE 10	// The lower, the quicker the projectiles will spawn!!
typedef std::vector<supermotor::TransientObject> queue_of_despawnable_objects;

queue_of_despawnable_objects projectiles;





SDL_FRect screen_center_rect{
    .x = WINDOW_WIDTH_F  / 2.0f,
    .y = WINDOW_HEIGHT_F / 2.0f,
    .w = 0.0f,
    .h = 0.0f
};



SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH_F,
    .h = WINDOW_HEIGHT_F
};



class Projectile : supermotor::TransientObject {
  private:
    int x_pos = WINDOW_HEIGHT / 2;       // Center of the screen by default.
    int y_pos = WINDOW_WIDTH / 2;       //  Center of the screen by default.

    int x_velocity = 0;
    int y_velocity = 0;



  public:

    // Constructor: Spawn a bullet in the center of the screen, and move it to any random direction.
    Projectile() : TransientObject(SDL_Texture* my_texture, int my_window_width, int my_window_height, Rect* position) : Rect (position) {
        x_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
        y_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
    }

    Projectile() : TransientObject(SDL_Texture* my_texture, int my_window_width, int my_window_height, Rect* position) : Rect (position) {
        x_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
        y_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
    }


    // Getters.


    // Setters.
    shoot_downwards_only() {
        x_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
        y_velocity = SDL_rand (0,  2);      //  0 <= x <= 1
    }


    // If you want to shoot in a specific ("exact") direction.
    shoot_direction_exact(int given_x_velocity, int given_y_velocity) {
        x_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
        y_velocity = SDL_rand (0,  2);      //  0 <= x <= 1
    }


    // If you want to shoot in a specific direction "range".
    shoot_direction_range(int given_x_velocity, int given_y_velocity) {
        x_velocity = SDL_rand (-1, 2);      // -1 <= x <= 1
        y_velocity = SDL_rand (0,  2);      //  0 <= x <= 1
    }



    // Change the speed of the bullets by a given factor.
        // Examples:
            // speedup(0.1) will make this bullet move 10 times slower.
            // speedup(1)   will not change this bullet's speed.
            // speedup(10)  will make this bullet move 10 times faster.
    speedup(int speedup_factor) {
        x_velocity *= speedup;
        y_velocity *= speedup;
    }




    
};


// shoot_wavy_sine(...)
// shoot_wavy_cosine(...)

#endif
