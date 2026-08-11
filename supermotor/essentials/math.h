#ifndef MATH_HEADER_FILE
#define MATH_HEADER_FILE


// Euclidean distance, as opposed to Manhattan distance.
// 
// Euclidean distance is continuous,
// whereas Manhattan distance is discrete.
//
// if you are unsure, I recommend using euclidean distances.


// #include <SDL3/SDL.h>
// #include <SDL3/SDL_stdinc.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>


// extern double SDL_pow(double a, double b);

/*

// I didn't get to use this cool union datatype, but
// you can use this if you want :D
//
union number {
	int a;
    float b;
	double c;
};

*/




template <typename T>
T manhattanDistance(T a, T b) {
    return ((abs)(b - a));
}



// You can change the datatype of the length to Uint32 or Uint64 if you want something bigger :3
//
template <typename T>
T manhattanDistance(T* a, T* b, unsigned short int length) {
    
    T total_distance = 0;

    while (length > 0) {
        total_distance += manhattanDistance(a[length - 1], b[length - 1]);
        length--;
    }

    // "Base case": when length == 0.
    return total_distance;
}




// You can change the datatype of the dimensions to Uint32 or Uint64 if you want something bigger :3
//
double euclideanDistance(double *a, double *b, unsigned short int dimensions) {

    double radicand = 0; // Don't worry about the recursion, it should be in a different stack frame... I think ":3.   

    while (dimensions > 0) {
        radicand  +=  (a[dimensions - 1] - b[dimensions - 1]) * (a[dimensions - 1] - b[dimensions - 1]);
        dimensions--;
    }

    // "Base case": when dimensions == 0.
    return sqrt(radicand);
}



#endif
