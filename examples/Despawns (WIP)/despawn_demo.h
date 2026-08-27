#ifndef DESPAWN_DEMO_HEADER_FILE
#define DESPAWN_DEMO_HEADER_FILE

#include "../../supermotor/math.h"
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




#endif
