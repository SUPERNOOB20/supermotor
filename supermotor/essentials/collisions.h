#ifndef COLLISIONS_HEADER_FILE
#define COLLISIONS_HEADER_FILE


#include <SDL3/SDL.h>
#include <iostream>
#include <array>

#include <vector>
#include <cassert>


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

      //  vvvv  Attributes  vvvv
      private:

      	// Don't worry, it's just (x1, y1), (x2, y2)
      	int top_left_corner[2]     = {};         
      	int bottom_right_corner[2] = {};
        

      // There will be a lot of overlapping in the public methods, for the sake of comfort
      // (The bigger the interface, the better! :3)
      //  vvvv  Constructors  vvvv
      public:


        
        // Attempt at a copy-constructor...
        Rect(Rect* og_rect)     // NO idea why this consumes Rect* instead of Rect. If you know, please tell me...
        {
        	top_left_corner[0] = og_rect->get_top_left_corner_x();
            top_left_corner[1] = og_rect->get_top_left_corner_y();
            bottom_right_corner[0] = og_rect->get_bottom_right_corner_x();
            bottom_right_corner[1] = og_rect->get_bottom_right_corner_y();          

            // SDL_Log("%s", "Rect's Constructor #1 has been used");
        }
        


        // Rect(std::array<int, 2> top_left_corner, std::array<int, 2> bottom_right_corner) {return {get_bottom_left_corner_x(), get_bottom_left_corner_y()} ;}
        Rect(int p1[2], int p2[2])
        {
        	top_left_corner[0] = p1[0];
            top_left_corner[1] = p1[1];
            bottom_right_corner[0] = p2[0];
            bottom_right_corner[1] = p2[1];

            // SDL_Log("%s", "Rect's Constructor #2 has been used");
        }

        Rect(std::array<std::array<int, 2>, 2> top_left_and_bottom_right_corners)
        {
        	top_left_corner[0] = top_left_and_bottom_right_corners[0][0];
            top_left_corner[1] = top_left_and_bottom_right_corners[0][1];
            bottom_right_corner[0] = top_left_and_bottom_right_corners[1][0];
            bottom_right_corner[1] = top_left_and_bottom_right_corners[1][1];

            // SDL_Log("%s", "Rect's Constructor #3 has been used");
        }

        // Converts SDL_FRect to supermotor::Rect  :3
        Rect(SDL_FRect sdl_rect)
        {
            top_left_corner[0] = sdl_rect.x;
            top_left_corner[1] = sdl_rect.y;
            bottom_right_corner[0] = sdl_rect.x + sdl_rect.w;
            bottom_right_corner[1] = sdl_rect.y + sdl_rect.h;

            // SDL_Log("%s", "Rect's Constructor #4 has been used");
        }



        //  vvvv  Getters  vvvv

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


        //  vvvv  Setters  vvvv

        void set_top_left_corner_x(int new_x_value) {
            int delta_x = top_left_corner[0] - new_x_value;       // delta_x = current_x_pos - new_x_pos;
            top_left_corner[0]       =  new_x_value;
            bottom_right_corner[0]  +=  delta_x;
        }

        void set_top_left_corner_y(int new_y_value) {
            int delta_y = top_left_corner[1] - new_y_value;       // delta_x = current_x_pos - new_x_pos;
            top_left_corner[1]       =  new_y_value;
            bottom_right_corner[1]  +=  delta_y;
        }

        void set_bottom_right_corner_x(int new_x_value) {
            int delta_x = bottom_right_corner[0] - new_x_value;       // delta_x = current_x_pos - new_x_pos;
            bottom_right_corner[0]    =  new_x_value;
            top_left_corner[0]       +=  delta_x;
        }

        void set_bottom_right_corner_y(int new_y_value) {
            int delta_y = bottom_right_corner[1] - new_y_value;       // delta_x = current_x_pos - new_x_pos;
            bottom_right_corner[1]    =  new_y_value;
            top_left_corner[1]       +=  delta_y;
        }

        void set_top_right_corner_x(int new_x_value) {
            int delta_x = get_top_left_corner_x() - new_x_value;
            top_left_corner[0]     += delta_x;
            bottom_right_corner[0] += delta_x;
        }

        void set_top_right_corner_y(int new_y_value) {
            int delta_y = get_top_left_corner_y() - new_y_value;
            top_left_corner[1]     += delta_y;
            bottom_right_corner[1] += delta_y;
        }

        void set_bottom_left_corner_x(int new_x_value) {
            int delta_x = get_bottom_left_corner_x() - new_x_value;
            top_left_corner[0]     += delta_x;
            bottom_right_corner[0] += delta_x;
        }

        void set_bottom_left_corner_y(int new_y_value) {
            int delta_y = get_bottom_left_corner_y() - new_y_value;
            top_left_corner[1]     += delta_y;
            bottom_right_corner[1] += delta_y;
        }


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


        // (Explicit) destructor
        ~Rect(){}

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
    void handle_collisions(Rect previous_player_pos, Rect current_player_pos, std::vector<Rect> obstacles) {


        // Previously int new_player_pos[] = {current_player_pos->get_top_left_corner_x(), current_player_pos->get_top_left_corner_y()};
        // This is a much better approach, with copy constructors:
        Rect new_player_pos(current_player_pos);


        // "For obstacle in obstacles":
        for (int i = 0; i < obstacles.size(); i++){
            Rect current_obstacle = obstacles[i];
            std::vector<int> current_collisions = collidingVertices(new_player_pos, current_obstacle);     // Implicit cast from to std::vector<int> to int[] (I hope it works...)
            unsigned short int number_of_colliding_vertices = current_collisions.size();

            switch(number_of_colliding_vertices) {
              case 1:

                int horizontal_clip_distance; 
                int vertical_clip_distance;


                // Here's something interesting if you want to improve this code further:
                // Player's snapped corner is always the opposite as the block's colliding corner 
                // (look at a visualization if it's not entirely obvious to you :3)
                switch (current_collisions[0]){
                    case 0:                   // Player has crashed into the top left corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos.get_top_left_corner_x() - current_obstacle.get_top_left_corner_x();
                        vertical_clip_distance    = new_player_pos.get_top_left_corner_y() - current_obstacle.get_top_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_bottom_right_corner_y(current_obstacle.get_top_left_corner_x() - 1);       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos.set_bottom_right_corner_y(current_obstacle.get_top_left_corner_y() - 1);       //  "Snaps" the player above the obstacle.
                        }

                        break;

                    case 1:           // Player has crashed into the top right corner of the obstacle.

                        horizontal_clip_distance  = new_player_pos.get_top_right_corner_x() - current_obstacle.get_top_right_corner_x();
                        vertical_clip_distance    = new_player_pos.get_top_right_corner_y() - current_obstacle.get_top_right_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_bottom_left_corner_y(current_obstacle.get_top_right_corner_x() + 1);       //  "Snaps" the player to the right of the obstacle.
                        } else {
                            new_player_pos.set_bottom_left_corner_y(current_obstacle.get_top_right_corner_y() - 1);       //  "Snaps" the player above the obstacle.
                        }

                        break;


                    case 2:           // Player has crashed into the bottom left corner of the obstacle.

                        horizontal_clip_distance  = new_player_pos.get_bottom_left_corner_x() - current_obstacle.get_bottom_left_corner_x();
                        vertical_clip_distance    = new_player_pos.get_bottom_left_corner_y() - current_obstacle.get_bottom_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_top_right_corner_y(current_obstacle.get_bottom_left_corner_x() - 1);       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos.set_top_right_corner_y(current_obstacle.get_bottom_left_corner_y() + 1);       //  "Snaps" the player below the obstacle.
                        }

                        break;


                    case 3:        // Player has crashed into the bottom right corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos.get_bottom_right_corner_x() - current_obstacle.get_bottom_right_corner_x();
                        vertical_clip_distance    = new_player_pos.get_bottom_right_corner_y() - current_obstacle.get_bottom_right_corner_y();

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_top_left_corner_y(current_obstacle.get_bottom_right_corner_x() + 1);       //  "Snaps" the player to the right of the obstacle.
                        } else {
                            new_player_pos.set_top_left_corner_y(current_obstacle.get_bottom_right_corner_y() + 1);       //  "Snaps" the player below the obstacle.
                        }        
                }

                break;

              case 2:
                if ((current_collisions[0] == TOP[0]) && (current_collisions[1] == TOP[1])) {
                  new_player_pos.set_top_left_corner_y(current_obstacle.get_top_left_corner_y() - 1);
                } else if ((current_collisions[0] == RIGHT[0]) && (current_collisions[1] == RIGHT[1])) {
                  new_player_pos.set_top_left_corner_x(current_obstacle.get_top_right_corner_x() + 1);
                } else if ((current_collisions[0] == BOTTOM[0]) && (current_collisions[1] == BOTTOM[1])) {
                  new_player_pos.set_top_left_corner_y(current_obstacle.get_bottom_left_corner_y() + 1);
                } else {         // ((current_collisions[0] == LEFT[0]) && (current_collisions[1] == LEFT[1]))
                  new_player_pos.set_top_left_corner_x(current_obstacle.get_top_left_corner_x() - 1);
                }

                break;

              default:       // number_of_colliding_vertices == 4  (when the player is inside an obstacle, or an obstacle is inside a player)
                new_player_pos = previous_player_pos;   // Put the player back into a position where, presumably, no collisions were happening (if you want the player to die or suffer damage when a block is inside them, do damage/death hurtbox logic instead (NOT hitbox logic)).      //      NO IDEA WHY * DOESN'T GO HERE AAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }

        current_player_pos = new_player_pos;
        return;
        }
    }

    Rect convert_sdl_rect_to_supermotor_rect(SDL_FRect my_rect){
        Rect converted_rect(my_rect);   // Calls "Rect(sdl_rect)".
        return converted_rect;
    }


    // Copies src_rect to dst_rect.
    // Overwrites ("pisa") the given SDL_FRect
    SDL_FRect* copy_supermotor_rect_to_sdl_rect(Rect* &src_rect, SDL_FRect* &dst_rect){    

        dst_rect->x = src_rect->get_top_left_corner_x();
        dst_rect->y = src_rect->get_top_left_corner_y();
        dst_rect->w = src_rect->get_bottom_right_corner_x() - src_rect->get_top_left_corner_x();     // Distance between the right edge and the left   edge of src_rect.
        dst_rect->h = src_rect->get_bottom_right_corner_y() - src_rect->get_top_left_corner_y();    //  Distance between the top   edge and the bottom edge of src_rect.

        return dst_rect;
    }


    // Vector version of Rect(sdl_rect).
    // If you want to use this for any other data structure, I recommend making this into a template...
    void handle_collisions(Rect previous_player_pos, Rect current_player_pos, std::vector<SDL_FRect> obstacles) { 
  
        std::vector<Rect> converted_obstacles = {};

        for (int i = 0; i < obstacles.size(); i++){

            Rect current_obstacle = convert_sdl_rect_to_supermotor_rect(obstacles[i]);
            converted_obstacles.push_back(current_obstacle);
        }


        // SDL_Log("obstacles.size(): %ld", obstacles.size());
        // SDL_Log("converted_obstacles.size(): %ld", converted_obstacles.size());
        assert (obstacles.size() && converted_obstacles.size());

        handle_collisions(previous_player_pos, current_player_pos, converted_obstacles);
    }
}



#endif
