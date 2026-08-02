#ifndef SCREENSHOTS_HEADER_FILE
#define SCREENSHOTS_HEADER_FILE

#include <SDL3/SDL.h>
#include <filesystem>



// WIP function. This doesn't work just yet! If you want to finish it, just transfer the SDL_PixelFormat from one place to the other...
/*
SDL_Surface* CreateSurfaceFromTexture(SDL_Texture* my_texture){


    int width  = my_texture.w; 
    int height = my_texture.h;

    std::array<std::array<int, width>, height> screenshot_data;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            current_pixel = SDL_GetRGB(i*j);
            screenshot_data[i][j] = current_pixel;       // Try    screenshot_data[i, j] = current_pixel;    if [i][j] doesn't work e.e
        }
    }

    // RGB ---> Surface
    SDL_Surface* screenshot SDL_CreateSurfaceFrom(int width, int height, SDL_PixelFormat format, void *pixels, int pitch);
}
*/







// Return an available filepath, to avoid overwriting...
// ...
std::string get_available_filepath(std::string directory){

    std::string filepath_candidate = directory + __TIME__ + ".png";      // Could also be any other desired format, like bmp or ppm, for instance.

    while (exists (filepath_candidate)){
        filename_candidate = directory + __TIME__ + ".png";
    }

    return filename_candidate;
}







void take_screenshot(SDL_Surface* my_surface){

    std::string filename = get_available_filename("./Screenshots/");

    // Saves the screenshot.
    SavePNG(screenshot, filename.c_str());
}



void take_screenshot(SDL_Window* my_window){

    SDL_Surface* screenshot = SDL_GetWindowSurface(my_window);

    take_screenshot(screenshot);
    std::string filepath = get_available_filepath("./Screenshots/");

    // Saves the screenshot.
    SavePNG(screenshot, filename.c_str());
}




// WIP e.e
/*
void take_screenshot(SDL_Texture* my_texture){

    take_screenshot(take_screenshot(CreateSurfaceFromTexture(my_texture)));

}
*/




#endif
