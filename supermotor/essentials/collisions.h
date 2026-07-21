#include <SDL3/SDL.h>
#include <iostream>
#include <array>


// See the attached drawing for more information.
int TOP[] = {0, 1};
int RIGHT[] = {1, 2};
int BOTTOM[] = {2, 3};
// int LEFT[] = {0, 3};




namespace supermotor
{


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

        // std::array<std::array<int, 2>, 4>   get_all_corners()   { return {{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}}; }
        // std::array<std::array<int, 2>, 4>   get_all_corners()   { return res{{{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}}}; }
        std::array<std::array<int, 2>, 4>   get_all_corners()   { return {{{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}}}; }

        // Shifts your Rect by x pixels.
        void move_x(int amount){
            top_left_corner[0]     += amount;
            bottom_right_corner[0] += amount;
        }

        // Shifts your Rect by y pixels.
        void move_y(int amount){
            top_left_corner[1]     += amount;
            bottom_right_corner[1] += amount;
        }

    };

    // Returns which vertices (0, 1, 2, or 3) collide between the two rectangles.
    // (the output will have 0, 1, 2, or 4 length).
    //
    // Example #1: res = [0, 1] means you're standing on the floor.
    // Example #2: res = [2, 3] means you're hitting a ceiling.
    // Example #3: res = [1] means you're hitting a top-right corner.
    std::vector<int> collidingVertices(Rect a, Rect b){

        std::vector<int> res;      // If you want to further optimise collisions, changing std::vector for a resizable array would be a good idea ":3

        std::array<std::array<int, 2>, 4> b_corners = b.get_all_corners();

        for (int corner = 0; corner < 4; corner++) {
            if ((a.get_top_left_corner_x() < b_corners[corner][0]) && (a.get_top_left_corner_y() < b_corners[corner][1]) && (b_corners[corner][0] < a.get_top_right_corner_x()) && (b_corners[corner][1]) < a.get_top_right_corner_y()) {
                res.push_back(corner);
            }
        }
        
        return res;
    }



    // This whole collision system works with the origin ((0, 0)) being the top-left corner of the screen (do not violate this invariant).
    // player_pos = [player_x, player_y]
    void handle_collisions(Rect previous_player_pos[], Rect current_player_pos[], std::vector<Rect> obstacles) {

        int new_player_pos[] = {current_player_pos.get_top_left_corner_x(), current_player_pos.get_top_left_corner_y()};

        // "For obstacle in obstacles":
        for (int i = 0; i < obstacles.length; i++){
            Rect current_obstacle = obstacles[i];
            int current_collisions[] = collidingVertices(player_pos, current_obstacle);     // Implicit cast from to std::vector<int> to int[] (I hope it works...)
            number_of_colliding_vertices = current_collisions.length();

            switch(number_of_colliding_vertices)
              case 1:

                switch (current_collisions[0]){
                    case 0:                   // Player has crashed into the top left corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos[0] - current_obstacle.get_top_left_corner_x();
                        vertical_clip_distance    = new_player_pos[1] - current_obstacle.get_top_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos[1] = current_obstacle.get_top_left_corner_x() - 1;       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos[1] = current_obstacle.get_top_left_corner_y() - 1;       //  "Snaps" the player above the obstacle.
                        }

                        break;

                    case 1:           // Player has crashed into the top right corner of the obstacle.

                        horizontal_clip_distance  = new_player_pos[0] - current_obstacle.get_top_right_corner_x();
                        vertical_clip_distance    = new_player_pos[1] - current_obstacle.get_top_right_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos[1] = current_obstacle.get_top_right_corner_x() + 1;       //  "Snaps" the player to the right of the obstacle.
                        } else {
                            new_player_pos[1] = current_obstacle.get_top_right_corner_y() - 1;       //  "Snaps" the player above the obstacle.
                        }

                        break;


                    case 2:           // Player has crashed into the bottom left corner of the obstacle.

                        horizontal_clip_distance  = new_player_pos[0] - current_obstacle.get_bottom_left_corner_x();
                        vertical_clip_distance    = new_player_pos[1] - current_obstacle.get_bottom_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos[1] = current_obstacle.get_bottom_right_corner_x() + 1;       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos[1] = current_obstacle.get_bottom_right_corner_y() + 1;       //  "Snaps" the player above the obstacle.
                        }

                        break;


                    case 3:        // Player has crashed into the bottom right corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos[0] - current_obstacle.get_bottom_right_corner_x();
                        vertical_clip_distance    = new_player_pos[1] - current_obstacle.get_bottom_right_corner_y();

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos[1] = current_obstacle.get_bottom_left_corner_x() - 1;       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos[1] = current_obstacle.get_bottom_left_corner_y() + 1;       //  "Snaps" the player above the obstacle.
                        }        

              break;

              case 2:
                if ((current_collisions[0] == TOP[0]) && (current_collisions[1] == TOP[1])) {
                  new_player_pos[1] = current_obstacle.get_top_left_corner_y() - 1;
                } else if ((current_collisions[0] == RIGHT[0]) && (current_collisions[1] == RIGHT[1])) {
                  new_player_pos[0] = current_obstacle.get_top_right_corner_x() + 1;
                } else if ((current_collisions[0] == BOTTOM[0]) && (current_collisions[1] == BOTTOM[1])) {
                  new_player_pos[1] = current_obstacle.get_bottom_left_corner_y() + 1;
                } else {         // ((current_collisions[0] == LEFT[0]) && (current_collisions[1] == LEFT[1]))
                  new_player_pos[0] = current_obstacle.get_top_left_corner_x() - 1;
                }

              break;

              default:       // number_of_colliding_vertices == 4  (when the player is inside an obstacle, or an obstacle is inside a player)
                new_player_pos = previous_player_pos;   // Put the player back into a position where, presumably, no collisions were happening.

        current_player_pos.new_player_pos
        return;
    }
}
