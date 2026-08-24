#ifndef DEMO_HEADER_FILE
#define DEMO_HEADER_FILE


#include <string>
#include <cassert>

#include "../../supermotor/essentials/storage.h"

#define WINDOW_WIDTH     (1280)
#define WINDOW_HEIGHT     (720)

#define WINDOW_WIDTH_F   (1280.0f)
#define WINDOW_HEIGHT_F   (720.0f)


// ------- BRUSH SETTINGS (SIZE and COLOUR) ------------------------------------------------------------------------
#define BRUSH_SIZE (49.0f)
#define MOUSE_CENTER (BRUSH_SIZE / 2.0f)        // Rellocates .x and .y from "top left" to "center" (see anchor.h for a more advanced anchor toolkit :3)

#define BRUSH_COLOR_R 0x00
#define BRUSH_COLOR_G 0x13
#define BRUSH_COLOR_B 0xBD
// -----------------------------------------------------------------------------------------------------------------



float mouse_pos_x = 0;
float mouse_pos_y = 0;


SDL_FRect Background{
    .x = 0.0f,
    .y = 0.0f,
    .w = WINDOW_WIDTH_F,
    .h = WINDOW_HEIGHT_F
};


SDL_FRect Brush{
    .x = mouse_pos_x  +  MOUSE_CENTER,
    .y = mouse_pos_y  +  MOUSE_CENTER,
    .w = BRUSH_SIZE,
    .h = BRUSH_SIZE
};



#endif
