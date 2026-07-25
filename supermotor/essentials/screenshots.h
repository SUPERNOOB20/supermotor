#ifndef SCREENSHOTS_HEADER_FILE
#define SCREENSHOTS_HEADER_FILE



// Return an available filename, to avoid overwriting...
// ...
std::string get_available_filename(std::string directory){

    Do whichever string manipulation necessary here...
    std::string filename = "screenshot.ppm";
}


void take_screenshot(unsigned short int window_width, unsigned short int window_height){

    std::vector<int> screenshot;

    for (int i = 0; i < window_height; i++) {
        for (int j = 0; j < window_width; j++) {
            current_pixel = SDL_GetRGB()
            screenshot.push_back()
        }
    }



    std::string filename = get_available_filename("./Screenshots");
    save_file(filename);
}


#endif
