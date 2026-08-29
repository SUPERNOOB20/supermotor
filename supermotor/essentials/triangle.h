// About the "check_colliders()" function: It receives "(v1, v2, vA, vC)", where:

// v1 is vertex 1. Format must be: v1 = (x1_coordinate, y1_coordinate)
// v2 is vertex 2 Format must be: v2 = (x2_coordinate, y2_coordinate)
// vA is an arbitrary vertex: a point inside the region to be detected! Format must be: vA = (xA_coordinate, yA_coordinate)
// vC is the vertex to check if it's inside the region or not... you usually want this one to be the mouse position :3 ---> vC = (mouse_x_pos, mouse_y_pos)

// ------------------------------------------------------------------------------------------------

// from this library we will be using "check_colliders_init" and "check_colliders"

// What the code does is:
// check_colliders_init() needs to be given the 3 vertices of your triangle AND a vertex inside the triangle. It returns the (bool, bool, bool) combination for your triangle. Useful to calculate the collider preemptively, outside event loops!
// check_colliders() needs to be given (v0, v1, v2, check_colliders_init(), vC), where vC is the vertex of the player position or cursor position that you want to check is inside the triangle or not :)

// The way the code works is... it finds the (bool, bool, bool) combination for vA, then the (bool, bool, bool) combination for vC.
// If the (bool, bool, bool) combinations are the same, the player is inside the triangle, and returns True. Otherwise, the player is outside the triangle, so it returns False.

// ALSO REMEMBER TO MAKE ALL THE COORDS SCALE WITH WINDOW RES (window height and window width) so that the proportions are kept the same no matter how much a player resizes their window :3

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#include <array>
#include "geometry.h"






Line finds_line_equation(Vertex vertex_1, Vertex, Vertex vertex_2) {       // Extends the given line to fit the whole screen by finding its closed formula! So basically finds a and b so that line = a * x + b. Some odd dudes call it mx + b. Pay those no mind :p
	Line line_formula(vertex_1, vertex_2);
    return line_formula;                   // It's a line! f(x) = m * x + b  (where "m" is the slope, and b are the ordinates).
}


std::array<bool, 3> check_colliders_init(Triangle triangle, Vertex vertex_A) {   // Looks for the (bool, bool, bool) combination for vA

    Line line_1 = finds_line_equation(triangle.get_vertex_1(), triangle.get_vertex_2());
    Line line_2 = finds_line_equation(triangle.get_vertex_2(), triangle.get_vertex_3());
    Line line_3 = finds_line_equation(triangle.get_vertex_3(), triangle.get_vertex_1());

    std::array<Line, 3> lines = {line_1, line_2, line_3};

    std::array<bool, 3> vertex_AC = {};

    for (Line line : lines) {

        bool res;

        if (type(line.get_slope()) == str) {     //  if the line is a vertical one...
            res = (line.ordinates() < vertex_A.x_coordinate());    // here, line.ordinates() is just the x value of the vertical line (sorry for notation abuse, coding is hard... e.e) 
        } else {
            res = (vertex_A.y_coordinate() <= line.get_slope() * vertex_A.get_x_coordinate() + line.get_ordinates());          // line[0] is a // line [1] is b // vA[0] is x_v // vA[1] is y_v
        }
        vertex_AC[line] = res;
    }
    
    // SDL_Log("lines_combination (vertex_AC) is: ", vertex_AC);
    return vertex_AC;
}


bool check_colliders(triangle: Triangle, vertex_AC: list[bool], vertex_C: Vertex) {   // vertex_AC is the [bool, bool, bool] combination for vertex_A

    rescaled_vertex_C_x_coordinate = floor(vertex_C.x_coordinate())
    rescaled_vertex_C_y_coordinate = floor(vertex_C.y_coordinate())

    rescaled_vertex_C = Vertex(rescaled_vertex_C_x_coordinate, rescaled_vertex_C_y_coordinate)  // We have to rescale user input!!! Because their screen might not be the same as the game resolution!":3


    std::array<bool, 3> vertex_CC = {false, false, false} // Initializes vertex_CC
    
    vertex_CC = check_colliders_init(triangle, rescaled_vertex_C);


    return vertex_AC == vertex_CC;   // vertex_CC is the combination calculated based on where the player/cursor is currently located at! :3
}




/*

"""
def check_against_initialized_colliders(triangle: Triangle, bool_list: list[bool], vertex):
    check_for_current_triangle = check_colliders(triangle, Vertex)
    return
"""
    

"""
if __name__ == "__main__":

    def tests_yellow():
        y_v0 = (1114, 421)
        y_v4 = (1267, 135)
        y_v5 = (1495, 346)

        y_cv2 = (1306, 292)

        vC = (900,200)

        print("Should be True: ", check_colliders(y_v0, y_v4, y_v5, (check_colliders_init(y_v0, y_v4, y_v5, y_cv2)), vC))


    tests_yellow()
"""

*/