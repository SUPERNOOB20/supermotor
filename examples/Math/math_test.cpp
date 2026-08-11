#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include "../../supermotor/essentials/math.h"
#include <iostream>

// extern double SDL_pow(double a, double b);

int main() {

    double a[3]  =  {1, 0, 5};
    double b[3]  =  {2, 5, 7};

    
    printf("\n");

    printf("manhattan distance between (1, 0, 5) and (2, 5, 7): %f\n", manhattanDistance(a, b, 3));
    printf("euclidean distance between (1, 0, 5) and (2, 5, 7): %f",   euclideanDistance(a, b, 3));

    printf("\n\n");

    return 0;
}


// template <typename T> manhattanDistance;
// template <typename T> euclideanDistance;
