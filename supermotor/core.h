#ifndef SUPERCORE20
#define SUPERCORE20





#include <bits/stdc++.h>
#include <vector>
#include <SDL3/SDL.h>
#include <stdio.h>


#include <cassert>

// https://cplusplus.com/forum/beginner/34572/
/*
char* strcatc( char* s, char c ) {
    char cs[ 2 ] = { c, '\0' };
    return strcat( s, cs );
}
*/


// Source - https://stackoverflow.com/a/6303595
// Posted by Tom, modified by community. See post 'Timeline' for change history
// Retrieved 2026-07-18, License - CC BY-SA 3.0
/*
std::string trim(std::string foo){
    size_t sep == std::string::npos;
    if(sep != string::npos) { name.resize(sep); }
}
*/


// Only works with fixed sizes (three characters in this case, .XXX) because I'm lazy ":3
// (but I might generalise this in the future...! I just don't really have the need to at the moment...)
// 
// Overall idea:
// 1) Reverse the filename.
// 2) Pick the first four characters.
// 3) Reverse them again.
// 4) allocated_file_extension_c_str will be the "box" in which we will put our result
//    (due to technical reasons, you can't return strings in C/C++ without a "box" like this...)
// 5) Put our file extension in that box (strcpy will do)
// 6) Return the box.
// NOTE: We don't free the box because it gets converted to C++ style and RAII frees the box for us (I think).
std::string find_file_format(std::string current_filename){

    std::string emanelif_tnerruc = current_filename;
    std::reverse((emanelif_tnerruc).begin(), (emanelif_tnerruc).end());     // .emanelif desreveR


    char a = emanelif_tnerruc[0];
    char b = emanelif_tnerruc[1];
    char c = emanelif_tnerruc[2];
    char d = emanelif_tnerruc[3];

    char* allocated_file_extension_c_str = (char*) malloc(5 * sizeof(char));       // Can't return strings in C/C++  :c
    char file_extension_c_str[]          = {d, c, b, a, 0};                       // .png

    assert (sizeof(file_extension_c_str) && sizeof(allocated_file_extension_c_str));    
    strcpy(allocated_file_extension_c_str, file_extension_c_str);   // Should be the same as strncpy(allocated_file_extension_c_str, file_extension_c_str, 5);

    std::string file_extension = file_extension_c_str;

    return file_extension;
}






namespace supermotor
{



    // Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
    // (DO NOT run this on your game loop)
    //
    SDL_Texture* generate_texture(SDL_Renderer* your_renderer, std::string filename){

        // SDL_Log("%s", filename.c_str());
        SDL_Texture* currentTexture;
     
        std::string file_extension = find_file_format(filename);
        
        const char* current_filename = filename.c_str();
        
        SDL_Surface* currentSurface;
        if (file_extension == ".png") {
            currentSurface = SDL_LoadPNG(current_filename);
        } else if (file_extension == ".bmp") {
            currentSurface = SDL_LoadBMP(current_filename);
        // } else if (file_extension == ".jpg") {                                       // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            // currentSurface = SDL_LoadJPG(current_filename);                         //  UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        } else {
            SDL_Log("file extension: %s", file_extension.c_str());
            SDL_Log("ERROR at file %s", current_filename);
            // assert (0 && "Sorry, only .png, .bmp, and .jpg are compatible :c Your image either has the wrong extension or is not supported.");        // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            assert (0 && "Sorry, only .png, and .bmp are compatible :c Your image either has the wrong extension or is not supported.");                //    COMMENTATE   THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        }
        if (currentSurface == nullptr){
            SDL_Log("file extension: %s", file_extension.c_str());
            SDL_Log("ERROR at file %s", current_filename);
		    assert(0 && "ERROR: File not found :c");
	    }

        // free(file_extension);

        currentTexture = SDL_CreateTextureFromSurface(your_renderer, currentSurface);
            
        return currentTexture;
    }








    // Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
    // (DO NOT run this on your game loop)
    //
    //
    //
    // Batch rendering implementations (should) go here.
    //
    // Input:  Your renderer and your filenames (as C strings)
    // Output: A vector with your textures ()
    //
    // NOTE: Only accepts .png, .jpg, and .bmp file formats.
    //       (If you want other file formats, you can ask me to implement one, or look for another tool yourself, such as this one ---> https://wiki.libsdl.org/SDL3_image/FrontPage)
    //       (for more info, read here ---> https://wiki.libsdl.org/SDL3/CategorySurface)
    //
    //
    std::vector<SDL_Texture*> generate_textures(SDL_Renderer* your_renderer, std::string image_filenames[], uint64_t number_of_files){
        
        std::vector<SDL_Texture*> your_textures;
        your_textures.resize() = number_of_files;

        for (int i = 0; i < number_of_files; i++){
            your_textures.push_back(generate_texture(your_renderer, image_filenames[i]));        
        }

        return your_textures;
    }
}



#endif
