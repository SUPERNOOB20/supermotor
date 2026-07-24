#ifndef COLLISIONS_HEADER_FILE
#define COLLISIONS_HEADER_FILE


#include <SDL3/SDL.h>
#include <iostream>
#include <array>

#include <vector>
#include <cassert>



// See the attached drawing for more information.
// These are the player's and NOT the obstacle's.
int TOP[] = {2, 3};
int RIGHT[] = {0, 2};
int BOTTOM[] = {0, 1};
int LEFT[] = {1, 3};




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

        int get_bottom_right_corner_x() { return bottom_right_corner[0]; }
        int get_bottom_right_corner_y() { return bottom_right_corner[1]; }

        int get_top_right_corner_x()    { return bottom_right_corner[0]; } 
        int get_top_right_corner_y()    { return top_left_corner[1]; }

        int get_bottom_left_corner_x()  { return top_left_corner[0]; }
        int get_bottom_left_corner_y()  { return bottom_right_corner[1]; }


        // Look at the attached visualization for more info...
        //
        // std::array<std::array<int, 2>, 4>   get_all_corners()   { return {{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}}; }
        // std::array<std::array<int, 2>, 4>   get_all_corners()   { return res{{{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}}}; }
        std::array<std::array<int, 2>, 4>   get_all_corners()   { return {{{top_left_corner[0], top_left_corner[1]}, {get_top_right_corner_x(), get_top_right_corner_y()}, {get_bottom_left_corner_x(), get_bottom_left_corner_y()}, {bottom_right_corner[0], bottom_right_corner[1]}}}; }


        //  vvvv  Setters  vvvv



        // Shifts your Rect by x pixels.
        void move_x(int amount){
            top_left_corner[0]     += amount;
            bottom_right_corner[0] += amount;

            /*
            if (amount != 0){
                SDL_Log("amount: %d", amount);
            }
            */

        }

        // Shifts your Rect by y pixels.
        void move_y(int amount){
            top_left_corner[1]     += amount;
            bottom_right_corner[1] += amount;
        }

        // Shifts your Rect by x, y pixels.
        void move_xy(int amount_x, int amount_y){
            move_x(amount_x);
            move_y(amount_y);
        }


        void set_top_left_corner_x(int new_x_value) {
            int delta_x = new_x_value - top_left_corner[0];       // delta_x = new_x_pos - current_x_pos;
            move_x(delta_x);
        }

        void set_top_left_corner_y(int new_y_value) {
            int delta_y = new_y_value - top_left_corner[1];       // delta_y = new_y_pos - current_y_pos;
            move_y(delta_y);
        }

        void set_bottom_right_corner_x(int new_x_value) {
            int delta_x = new_x_value - bottom_right_corner[0];       // delta_x = new_x_pos - current_x_pos;
            move_x(delta_x);
        }

        void set_bottom_right_corner_y(int new_y_value) {
            int delta_y =  new_y_value - bottom_right_corner[1];       // delta_y = new_y_pos - current_y_pos;
            move_y(delta_y);
        }

        void set_top_right_corner_x(int new_x_value) {
            int delta_x = new_x_value - get_top_right_corner_x();
            move_x(delta_x);
        }

        void set_top_right_corner_y(int new_y_value) {
            int delta_y = new_y_value - get_top_right_corner_y();
            move_y(delta_y);
        }

        void set_bottom_left_corner_x(int new_x_value) {
            int delta_x = new_x_value - get_bottom_left_corner_x();
            move_x(delta_x);
        }

        void set_bottom_left_corner_y(int new_y_value) {
            int delta_y = new_y_value - get_bottom_left_corner_y();
            move_y(delta_y);
        }


        // (Explicit) destructor
        ~Rect(){}

    };



    // a represents the player.
    // b represents an obstacle.
    //
    // Returns which vertices (0, 1, 2, or 3) collide between the two rectangles.
    // (the output will have 0, 1, 2, or 4 length).
    //
    // Example #1: res = [0, 1] means you're standing on the floor.
    // Example #2: res = [2, 3] means you're hitting a ceiling.
    // Example #3: res = [1] means you're hitting a top-right corner.
    std::vector<int> collidingVertices(Rect a, Rect b){

        std::vector<int> res;      // If you want to further optimise collisions, changing std::vector for a resizable array would be a good idea ":3

        std::array<std::array<int, 2>, 4> a_corners = a.get_all_corners();
        // std::array<std::array<int, 2>, 4> b_corners = b.get_all_corners();

        int b_x1 = b.get_top_left_corner_x();
        int b_y1 = b.get_top_left_corner_y();

        int b_x2 = b.get_bottom_right_corner_x();
        int b_y2 = b.get_bottom_right_corner_y();

        // Checks the whole obstacle against one player corner at a time (partial clippings of 1 corner).
        for (int corner = 0; corner < 4; corner++) {
            int a_x = a_corners[corner][0];
            int a_y = a_corners[corner][1];

            if ((a_x < b_x2) && (a_y < b_y2) && (b_x1 < a_x) && (b_y1 < a_y)) {
                res.push_back(corner);
            }
        }


        return res;
    }



    // This whole collision system works with the origin ((0, 0)) being the top-left corner of the screen (do not violate this invariant).
    // player_pos = [player_x, player_y]
    Rect handle_collisions(Rect previous_player_pos, Rect cur_player_pos, std::vector<Rect> obstacles) {

        Rect current_player_pos(cur_player_pos);

        // Previously int new_player_pos[] = {current_player_pos->get_top_left_corner_x(), current_player_pos->get_top_left_corner_y()};
        // This is a much better approach, with copy constructors:
        Rect new_player_pos(current_player_pos);


        // "For obstacle in obstacles":
        for (int i = 0; i < obstacles.size(); i++){
            Rect current_obstacle = obstacles[i];
            std::vector<int> current_collisions = collidingVertices(new_player_pos, current_obstacle);     // Implicit cast from to std::vector<int> to int[] (I hope it works...)
            unsigned short int number_of_colliding_vertices = current_collisions.size();

            /*
            if (number_of_colliding_vertices != 0){
                SDL_Log("\n");
                SDL_Log("number_of_colliding_vertices: %d", number_of_colliding_vertices);
                for (int i = 0; i < number_of_colliding_vertices; i++){
                    SDL_Log("current_collisions[i]: %d", current_collisions[i]);
                }
            }
            */

            switch(number_of_colliding_vertices) {
              case 0:
                break;
              case 1:

                int horizontal_clip_distance; 
                int vertical_clip_distance;


                // Here's something interesting if you want to improve this code further:
                // Player's snapped corner is always the opposite as the block's colliding corner 
                // (look at a visualization if it's not entirely obvious to you :3)
                switch (current_collisions[0]){
                    case 3:                   // Player has crashed into the bottom right? corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos.get_top_left_corner_x() - current_obstacle.get_top_left_corner_x();
                        vertical_clip_distance    = new_player_pos.get_top_left_corner_y() - current_obstacle.get_top_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_bottom_right_corner_x(current_obstacle.get_top_left_corner_x() - 1);       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos.set_bottom_right_corner_y(current_obstacle.get_top_left_corner_y() - 1);       //  "Snaps" the player above the obstacle.
                        }

                        break;

                    case 2:           // Player has crashed into the bottom left? corner of the obstacle.

                        horizontal_clip_distance  = new_player_pos.get_top_right_corner_x() - current_obstacle.get_top_right_corner_x();
                        vertical_clip_distance    = new_player_pos.get_top_right_corner_y() - current_obstacle.get_top_right_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_bottom_left_corner_x(current_obstacle.get_top_right_corner_x() + 1);       //  "Snaps" the player to the right of the obstacle.
                        } else {
                            new_player_pos.set_bottom_left_corner_y(current_obstacle.get_top_right_corner_y() - 1);       //  "Snaps" the player above the obstacle.
                        }

                        break;


                    case 1:           // Player has crashed into the top right? corner of the obstacle.

                        // SDL_Log("aaaaa");        
    
                        horizontal_clip_distance  = new_player_pos.get_bottom_left_corner_x() - current_obstacle.get_bottom_left_corner_x();
                        vertical_clip_distance    = new_player_pos.get_bottom_left_corner_y() - current_obstacle.get_bottom_left_corner_y();        

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_top_right_corner_x(current_obstacle.get_bottom_left_corner_x() - 1);       //  "Snaps" the player to the left of the obstacle.
                        } else {
                            new_player_pos.set_top_right_corner_y(current_obstacle.get_bottom_left_corner_y() + 1);       //  "Snaps" the player below the obstacle.
                        }

                        break;


                    case 0:        // Player has crashed into the top left? corner of the obstacle.
                    
                        horizontal_clip_distance  = new_player_pos.get_bottom_right_corner_x() - current_obstacle.get_bottom_right_corner_x();
                        vertical_clip_distance    = new_player_pos.get_bottom_right_corner_y() - current_obstacle.get_bottom_right_corner_y();

                        if (horizontal_clip_distance < vertical_clip_distance) {
                            new_player_pos.set_top_left_corner_x(current_obstacle.get_bottom_right_corner_x() + 1);       //  "Snaps" the player to the right of the obstacle.
                        } else {
                            new_player_pos.set_top_left_corner_y(current_obstacle.get_bottom_right_corner_y() + 1);       //  "Snaps" the player below the obstacle.
                        }        
                }

                break;

              case 2:

                // CAREFUL: I am still referring to the player and not the obstacle.
                // SDL_Log("trespassing...");

                if ((current_collisions[0] == BOTTOM[0]) && (current_collisions[1] == BOTTOM[1])) {
                  new_player_pos.set_top_left_corner_y(current_obstacle.get_bottom_left_corner_y() + 1);                            // SDL_Log("ceiling...");
                } else if ((current_collisions[0] == LEFT[0]) && (current_collisions[1] == LEFT[1])) {                  
                  new_player_pos.set_top_left_corner_x(current_obstacle.get_top_right_corner_x() + 1);                          // SDL_Log("right wall...");
                  SDL_Log("Noooooooooo");
                } else if ((current_collisions[0] == TOP[0]) && (current_collisions[1] == TOP[1])) {
                  new_player_pos.set_bottom_left_corner_y(current_obstacle.get_top_left_corner_y() - 1);                       // SDL_Log("floor...");
                } else {         // ((current_collisions[0] == RIGHT[0]) && (current_collisions[1] == RIGHT[1]))
                  new_player_pos.set_top_right_corner_x(current_obstacle.get_top_left_corner_x() - 1);                         // SDL_Log("left wall...");
                  assert (current_collisions[0] && RIGHT[0]);
                  assert (current_collisions[1] && RIGHT[1]);
                }

                break;

              default:       // number_of_colliding_vertices == 4  (when the player is inside an obstacle, or an obstacle is inside a player)
                new_player_pos = previous_player_pos;   // Put the player back into a position where, presumably, no collisions were happening (if you want the player to die or suffer damage when a block is inside them, do damage/death hurtbox logic instead (NOT hitbox logic)).      //      NO IDEA WHY * DOESN'T GO HERE AAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }


            // Updates player pos for the rest of the collision checking.        
            current_player_pos = new_player_pos;
        }


        return current_player_pos;  
    }



    Rect convert_sdl_rect_to_supermotor_rect(SDL_FRect my_rect){
        Rect converted_rect(my_rect);   // Calls "Rect(sdl_rect)".
        return converted_rect;
    }


    // Copies src_rect to dst_rect.
    // Overwrites ("pisa") the given SDL_FRect
    //
    // I tried to get this to work with pointers but I couldn't :c
    // If you want to optimise this function further, you can try to implement pointers for it (i.e passing Rect* and SDL_FRect* here instead of Rect and SDL_FRect e.e).
    SDL_FRect copy_supermotor_rect_to_sdl_rect(Rect src_rect, SDL_FRect dst_rect){    

        dst_rect.x = src_rect.get_top_left_corner_x();
        dst_rect.y = src_rect.get_top_left_corner_y();
        dst_rect.w = src_rect.get_bottom_right_corner_x() - src_rect.get_top_left_corner_x();     // Distance between the right edge and the left   edge of src_rect.
        dst_rect.h = src_rect.get_bottom_right_corner_y() - src_rect.get_top_left_corner_y();    //  Distance between the top   edge and the bottom edge of src_rect.

        
        return dst_rect;
    }


    // Vector version of Rect(sdl_rect).
    // If you want to use this for any other data structure, I recommend making this into a template...
    Rect handle_collisions(Rect previous_player_pos, Rect current_player_pos, std::vector<SDL_FRect> obstacles) { 
  
        std::vector<Rect> converted_obstacles = {};

        for (int i = 0; i < obstacles.size(); i++){

            Rect current_obstacle = convert_sdl_rect_to_supermotor_rect(obstacles[i]);
            converted_obstacles.push_back(current_obstacle);
        }


        // SDL_Log("obstacles.size(): %ld", obstacles.size());
        // SDL_Log("converted_obstacles.size(): %ld", converted_obstacles.size());
        assert (obstacles.size() && converted_obstacles.size());

        return handle_collisions(previous_player_pos, current_player_pos, converted_obstacles);
    }
}



#endif
