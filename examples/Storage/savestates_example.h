#ifndef SAVESTATES_EXAMPLE_HEADER_FILE
#define SAVESTATES_EXAMPLE_HEADER_FILE



#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720



#include <SDL3/SDL.h>
#include <string>
#include <cassert>
// #include <vector>
#include <tuple>



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



#endif
