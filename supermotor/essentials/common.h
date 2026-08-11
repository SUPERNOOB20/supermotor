#ifndef COMMON_HEADER_FILE
#define COMMON_HEADER_FILE




#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT   720

// Tape and prayers? Tape and prayers ":3
//
// NUDGE is kind of a leniency for hitting corners on ceilings.
// My recommendation is 0 nudge for top players,
// and higher and higher nudge for rookier and rookier players.
float nudge = (WINDOW_WIDTH / 40);


void update_nudge(){
    nudge = (WINDOW_WIDTH / 40);
}



double vertical_velocity = 0.0f;
double horizontal_velocity = 0.0f;



#endif
