#ifndef SAVESTATES_EXAMPLE_HEADER_FILE
#define SAVESTATES_EXAMPLE_HEADER_FILE



#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720



#include <SDL3/SDL.h>
#include <string>
#include <cassert>
// #include <vector>
#include <tuple>



// ------ Background and Akyuu --------

enum Direction {
    HORIZONTAL,
    VERTICAL  
};


SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT
};



SDL_FRect akyuu1_position {
    .x = WINDOW_WIDTH  * (1.0f / 7.0f),     // 1/7 padding.
    .y = WINDOW_HEIGHT / 4.0f,
    .w = WINDOW_HEIGHT / 6.0f,     // My sprite is 1:1 ratio, so .w = .h.
    .h = WINDOW_HEIGHT / 6.0f      // My sprite is 1:1 ratio, so .w = .h.
};


SDL_FRect akyuu2_position {
    .x = (WINDOW_WIDTH  * (6.0f / 7.0f)) - (WINDOW_HEIGHT / 6.0f),     // 1/7 padding.
    .y = WINDOW_HEIGHT / 4.0f,
    .w = WINDOW_HEIGHT / 6.0f,     // My sprite is 1:1 ratio, so .w = .h.
    .h = WINDOW_HEIGHT / 6.0f      // My sprite is 1:1 ratio, so .w = .h.
};





//  --------------------- OBSTACLES ---------------------

// std::vector<SDL_Texture*> your_textures_here;






SDL_FRect Floor{
    .x = 0,
    .y = WINDOW_HEIGHT  / 1.4f,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT / 2
};

SDL_FRect Platform1{
    .x = WINDOW_WIDTH  / 3.5f,
    .y = WINDOW_HEIGHT  / 5.0f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 4.0f
};


SDL_FRect Platform2{
    .x = WINDOW_WIDTH  / 1.5f,
    .y = WINDOW_HEIGHT  / 1.75f,
    .w = WINDOW_WIDTH  / 10.0f,
    .h = WINDOW_HEIGHT / 5.0f
};


SDL_FRect HighFloor1{
    .x = WINDOW_WIDTH   * 0.75f,
    .y = WINDOW_HEIGHT  / 1.75f,
    .w = WINDOW_WIDTH   / 3.0f,
    .h = WINDOW_HEIGHT  / 10.0f
};

SDL_FRect HighFloor2{
    .x = WINDOW_WIDTH   / 1.5f,
    .y = WINDOW_HEIGHT  / 1.75f,
    .w = WINDOW_WIDTH   / 3.0f,
    .h = WINDOW_HEIGHT  / 10.0f
};




#endif
