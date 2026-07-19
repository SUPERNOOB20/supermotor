#include <SDL3/SDL.h>
#include <iostream>
#include <array>

// Invariant (do not violate):
///// top_left_corner_x <= bottom_right_corner_x
///// top_left_corner_y <= bottom_right_corner_y
// .
// If for whatever reason you need to step over that invariant,
// you can try with abs(get_width()) and abs(get_height()).
class Rect {
  private:

  	// Don't worry, it's just (x1, y1), (x2, y2)
  	int top_left_corner[2]     = {};         
  	int bottom_right_corner[2] = {};
    
  // There will be a lot of overlapping in the public methods, for the sake of comfort
  // (The bigger the interface, the better! :3)
  public:

    // Rect(std::array<int, 2> top_left_corner, std::array<int, 2> bottom_right_corner) {return {get_bottom_left_corner_x(), get_bottom_left_corner_y()} ;}
    Rect(int p1[2], int p2[2])
    {
    	top_left_corner[0] = p1[0];
        top_left_corner[1] = p1[1];
        bottom_right_corner[0] = p2[0];
        bottom_right_corner[1] = p2[1];
    }

    Rect(std::array<std::array<int, 2>, 2> top_left_and_bottom_right_corners)
    {
    	top_left_corner[0] = top_left_and_bottom_right_corners[0][0];
        top_left_corner[1] = top_left_and_bottom_right_corners[0][1];
        bottom_right_corner[0] = top_left_and_bottom_right_corners[1][0];
        bottom_right_corner[1] = top_left_and_bottom_right_corners[1][1];
    }

    Rect(SDL_FRect sdl_rect)
    {
        top_left_corner[0] = sdl_rect.x;
        top_left_corner[1] = sdl_rect.y;
        bottom_right_corner[0] = sdl_rect.x + sdl_rect.w;
        bottom_right_corner[1] = sdl_rect.y + sdl_rect.h;
    }

    int get_width() { return top_left_corner[0] - bottom_right_corner[0]; }     // Should always be >= 0.
    int get_height() { return top_left_corner[1] - bottom_right_corner[1]; }    // Should always be >= 0.

    int get_top_left_corner_x()     { return top_left_corner[0]; }
    int get_top_left_corner_y()     { return top_left_corner[1]; }

    int get_bottom_right_corner_x() { return top_left_corner[0]; }
    int get_bottom_right_corner_y() { return top_left_corner[1]; }

    int get_top_right_corner_x()    { return bottom_right_corner[0]; } 
    int get_top_right_corner_y()    { return top_left_corner[1]; }

    int get_bottom_left_corner_x()  { return top_left_corner[0]; }
    int get_bottom_left_corner_y()  { return bottom_right_corner[1]; }

    

    // std::tuple get_top_left_corner_y = return top_left_corner[1];

};




// Returns which vertices (0, 1, 2, or 3) collide between the two rectangles.
// (the output will have 0, 1, 2, or 4 length).
//
// Example #1: res = [0, 1] means you're standing on the floor.
// Example #2: res = [2, 3] means you're hitting a ceiling.
// Example #3: res = [1] means you're hitting a top-right corner.
void* collidingVertices(Rect a, Rect b){

    void* void_ptr;
    int res[3] = {1, 2, 3};
    void_ptr = &res;

    return void_ptr;
}
