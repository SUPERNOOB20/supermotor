#ifndef SCREENSHOTS_HEADER_FILE
#define SCREENSHOTS_HEADER_FILE

#include <SDL3/SDL.h>
#include <filesystem>

#include <stdio.h>
#include <time.h>


namespace supermotor
{




//  Thanks to https://www.w3schools.com/c/c_date_time.php
//
//  Returns the current time.
//
std::string get_current_time(){

    time_t currentTime;
    time(&currentTime);

    std::string output = ctime(&currentTime);

    return output;    
}





// Return an available filepath, to avoid overwriting...
// ...
std::string get_available_filepath(std::string directory){

    

    std::string filepath_candidate = directory + get_current_time() + ".png";      // Could also be any other desired format, like bmp or ppm, for instance.

    int i = 0;

    while (std::filesystem::exists (filepath_candidate)){
        filepath_candidate = directory + get_current_time() + ".png";
        i++;
    }

    return filepath_candidate;
}






// Takes either CPU or GPU screenshot.
//
SDL_Surface* screenshot_surface = nullptr;
void take_screenshot(SDL_Window* my_window, SDL_Renderer* my_renderer){

    (my_renderer == nullptr) ? screenshot_surface = SDL_GetWindowSurface(my_window) : screenshot_surface = SDL_RenderReadPixels(my_renderer, nullptr);

    if (screenshot_surface == nullptr) {
        SDL_Log("%s", "WARNING: Nothing found to screenshot! No screenshot will be taken '^- ^");
    } else {

        std::string filename = get_available_filepath("./Screenshots/");

        // Saves the screenshot.
        (!SDL_SavePNG(screenshot_surface, filename.c_str()))  ?  SDL_Log("ERROR: Couldn't save your screenshot because... %s", SDL_GetError())  :  SDL_Log("Screenshot saved at: %s", filename.c_str());
    }


}


}

#endif
