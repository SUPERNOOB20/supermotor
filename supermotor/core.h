#ifndef SUPERCORE20
#define SUPERCORE20


#include <bits/stdc++.h>
#include <vector>
#include <SDL3/SDL.h>
#include <stdio.h>

#include <cassert>

#include <filesystem>
#include <map>

#include <algorithm>

// Welcome! :3)7
// core.h contains essential game engine functions like batch rendering.
//
// That is to say, you give it filenames, and it loads aaaall those images into the GPU.
// (you should run these only ONCE either on startup or on loading screens, and NOT every single frame of your game).
//
// Here are some ideas if you want to improve this code (or I might do these too, in the future...):
/////// * Implementing an alternative for find_file_formats() which uses malloc "(n * sizeof(my_largest_filename))" instead of n times malloc(sizeof(my_filename)) will use slightly more RAM but should perform considerably faster (HIGH performance impact)
/////// * Refactor std::vector into C-style arrays as much as you can (low priority...)
/////// * Refactor std::string into const char*    as much as you can (low priority...)


namespace supermotor
{


typedef std::vector<SDL_Texture*> textures;

union asset {
    SDL_Surface* surface;
    SDL_Texture* texture;
};

typedef std::vector<asset> assets;

typedef map<std::string, asset>



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
//
//
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


    // Example: find_filename("./foo/bar/dummy_file.txt") == "dummy_file.txt"
    //
    std::string find_filename(std::string filepath) {

        // "Cache" filepath length to avoid a bajillion unnecessary function calls.
        Uint64 filepath_length = filepath.length();

        std::reverse(filepath);      // .htapelif
        
        std::string filename = "";   // .emanelif

        i = 0;
        while ((filepath[i] != "/") && (i < filepath_length)) {
            filename += filepath[i]; 
            i++;
        }

        std::reverse(filename)       // filename.

        return filename;
    }



    // Could have just overloaded "generate_textures()" but meh, felt like it might be less confusing this way :3".
    asset_dict generate_assets_from_directory(SDL_Renderer* mRenderer, std::string filename) {

        asset_dict my_asset_dict = {{}};

        // Iterate over the std::filesystem::directory_entry elements using `auto`
        for (auto const& dir_entry : std::filesystem::recursive_directory_iterator("./")) {

            current_filepath = dir_entry.path();

            current_file = find_filename(current_filepath);

            my_asset_dict[current_file] = generate_asset(mRenderer, current_filepath);

            std::cout << dir_entry.path() << std::endl;
        }
    }



    // Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
    // (DO NOT run this on your game loop)
    //
    asset generate_asset(SDL_Renderer* your_renderer, std::string filename){

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
            assert (0 && "Sorry, only .png, and .bmp are compatible :c Your image either has the wrong extension or is not supported.");                //    COMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        }
        if (currentSurface == nullptr){
            SDL_Log("file extension: %s", file_extension.c_str());
            SDL_Log("ERROR at file %s", current_filename);
		    assert(0 && "ERROR: File not found :c");
	    }

        // free(file_extension);

        currentAsset.surface = currentSurface;

        if (your_renderer != nullptr) {
            currentTexture = SDL_CreateTextureFromSurface(your_renderer, currentSurface);
            currentAsset.texture = currentTexture;
            SDL_DestroySurface(currentSurface);
        }
            
        return currentAsset;
    }








    // Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
    // (DO NOT run this on your game loop)
    //
    //
    //
    // Batch rendering implementations (should) go here.
    //
    // Input:  Your renderer and your filenames (as C++ strings).
    // Output: A vector with your textures.
    //
    // NOTE: Only accepts .png, .jpg, and .bmp file formats.
    //       (If you want other file formats, you can ask me to implement one, or look for another tool yourself, such as this one ---> https://wiki.libsdl.org/SDL3_image/FrontPage)
    //       (for more info, read here ---> https://wiki.libsdl.org/SDL3/CategorySurface)
    //
    //
    assets generate_assets(SDL_Renderer* your_renderer, std::string image_filenames[], uint64_t number_of_files){
        
        assets your_assets;
        your_assets.resize(number_of_files);

        // Would rather repeat a chunk of code than check a pointer (n-1) times more :3
        if (your_renderer == nullptr) {

            for (int i = 0; i < number_of_files; i++){
                your_assets.push_back((generate_asset(your_renderer, image_filenames[i])).surface);        
            }
        
        } else {
        
            for (int i = 0; i < number_of_files; i++){
                your_assets.push_back((generate_asset(your_renderer, image_filenames[i])).texture);        
            }
        }


        return your_assets;
    }
}



#endif
