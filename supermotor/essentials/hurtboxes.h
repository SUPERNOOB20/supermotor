#ifndef HURTBOXES_HEADER_FILE
#define HURTBOXES_HEADER_FILE

#include <SDL3/SDL.h>



enum Hurtbox_Shape {
    RECT,         // 0
    TRIANGLE,     // 1
    CIRCLE        // 2
}

typedef unsigned short int shape

class Hurtbox {
  private:
    shape my_shape {TRIANGLE};        // Triangle as default value because spikes are spikey, but you can choose any default value (or no default value at all) depending on your game :3



  public:

    // Constructors.
    Hurtbox() {}
    Hurtbox(shape given_shape)          { my_shape = given_shape; }

    // Getters & Setters (do we really need a triangle transforming into a circle, though...?).
    shape get_shape()                   { return my_shape;        }
    void set_shape(shape given_shape)   { my_shape = given_shape; }
}


typedef std::vector<Hurtbox> Hurtboxes;



// Returns true if the player is touching the obstacle and should die. Returns false otherwise.
bool check_collision(SDL_Rect player_rect, Hurtbox hurtbox) {

    player_must_die = false;

    switch (hurtbox.shape) {
        case(RECT):
            player_must_die = SDL_HasRectIntersection(shape, player_rect);
        break;

        case(TRIANGLE):
            // player_must_die =   ... check the 3 lines ...
        break;

        case(CIRCLE):
            // player_must_die =   ... radius check ...
        break;

    }

    return player_must_die;
}



// Returns true if the player is touching the obstacle and should die. Returns false otherwise.
// I recommend you to run this every single frame.
bool check_collisions(SDL_Rect player_rect, Hurtboxes given_hurtboxes) {

    player_must_die = false;

    for (Hurtbox hurtbox : given_hurtboxes)    // Using references  (Read more here ---> https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/).
        player_must_die || check_collision(player_rect, hurtbox);       // The player will only live if all the collision checks are false :3


    return player_must_die;
}



// Example text here (example note here) bla bla bla :3.




#endif
