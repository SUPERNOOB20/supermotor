#ifndef ANCHORS_HEADER_FILE
#define ANCHORS_HEADER_FILE

// Various SDL_FRect utilities like anchors and rescaling :3


// -------  RESCALING  --------------------------------------------------------------------
template <typename T> SDL_FRect resize_rect (SDL_FRect rect, T scalar_factor) {
    rect.x *= scalar_factor;
    rect.y *= scalar_factor;
    rect.w *= scalar_factor;
    rect.h *= scalar_factor;

    return rect;
}




// -------  ANCHORS  ----------------------------------------------------------------------


enum operation {
    TOP_LEFT,       // 0
    TOP,            // 1
    TOP_RIGHT,      // 2
    RIGHT,          // 3
    DOWN_RIGHT,     // 4
    DOWN,           // 5
    DOWN_LEFT,      // 6
    LEFT            // 7
}




// Given rectangle A, and rectangle B, places rectangle B relative to rectangle A
// with the specified anchor.
//
// Check out the attached "explanation.png" if you are still confused.
// If you don't understand or want me to make a drawing to explain more easily what this does PLEASE let me know ":3
//
SDL_FRect anchor (unsigned short int operation, SDL_FRect rect_A, SDL_FRect rect_B) {
    
    return B;
}




/*
SDL_FRect resize_rect (SDL_FRect rect, scalar) {
    
    return ;
}
*/









#endif
