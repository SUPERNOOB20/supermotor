#ifndef ANCHORS_DEMO_2_HEADER_FILE
#define ANCHORS_DEMO_2_HEADER_FILE


#include <SDL3/SDL.h>
#include <string>
#include <cassert>

#include "../../../supermotor/GUIs/anchors.h"
#include "../../../supermotor/essentials/gallery.h"

#define WINDOW_WIDTH     (1280)
#define WINDOW_HEIGHT     (720)

#define WINDOW_WIDTH_F   (1280.0f)
#define WINDOW_HEIGHT_F   (720.0f)




SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH_F,
    .h = WINDOW_HEIGHT_F
};


SDL_FRect Container{
    .x = WINDOW_WIDTH_F * 0.7f,
    .y = WINDOW_HEIGHT_F * 0.5f,
    .w = WINDOW_WIDTH_F / 5.0f,
    .h = WINDOW_HEIGHT_F / 5.0f
};



#endif
