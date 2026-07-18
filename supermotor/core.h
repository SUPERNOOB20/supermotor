// Batch rendering implementations (should) go here.

// Input:  Your renderer and your filenames (as C strings)
// Output: A vector with your textures ()

// NOTE: Only accepts .png, .jpg, and .bmp file formats.
//       (If you want other file formats, you can ask me to implement one, or look for another tool yourself, such as this one ---> https://wiki.libsdl.org/SDL3_image/FrontPage)
//       (for more info, read here ---> https://wiki.libsdl.org/SDL3/CategorySurface)


#include <bits/stdc++.h>
#include <vector>
#include <SDL3/SDL.h>
#include <stdio.h>


#include <cassert>

// https://cplusplus.com/forum/beginner/34572/
char* strcatc( char* s, char c ) {
    char cs[ 2 ] = { c, '\0' };
    return strcat( s, cs );
}



// Source - https://stackoverflow.com/a/6303595
// Posted by Tom, modified by community. See post 'Timeline' for change history
// Retrieved 2026-07-18, License - CC BY-SA 3.0
/*
std::string trim(std::string foo){
    size_t sep == std::string::npos;
    if(sep != string::npos) { name.resize(sep); }
}
*/



// Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
// (DO NOT run this on your game loop)
std::vector<SDL_Texture*> generate_textures(SDL_Renderer* your_renderer, std::string image_filenames[], uint64_t number_of_files){
    

    std::vector<SDL_Texture*> your_textures;

    for (int i = 0; i < number_of_files; i++){

        SDL_Log("%s", image_filenames[i].c_str());
        SDL_Texture* currentTexture;

        std::string emanelif_tnerruc = image_filenames[i];
        std::reverse((emanelif_tnerruc).begin(), (emanelif_tnerruc).end());     // .emanelif desreveR
        
        char a = emanelif_tnerruc[0];
        char b = emanelif_tnerruc[1];
        char c = emanelif_tnerruc[2];
        char d = emanelif_tnerruc[3];
        
        char file_extension_c_str[] = {a, b, c, d, '\0'};

        std::string file_extension = file_extension_c_str;

        std::reverse((file_extension).begin(), (file_extension).end());
        SDL_Log("size: %ld", file_extension.length());
        SDL_Log("file_extension: %s", file_extension.c_str());
        std::reverse((emanelif_tnerruc).begin(), (emanelif_tnerruc).end());
        emanelif_tnerruc = emanelif_tnerruc.c_str();


        SDL_Surface* currentSurface;
        
        const char* current_filename = image_filenames[i].c_str();

        /*
        switch (file_extension) {
            case ".png":
                SDL_Surface* currentSurface = SDL_LoadPNG(image_filenames[i]);
                break;
            case ".bmp":
                SDL_Surface* currentSurface = SDL_LoadBMP(image_filenames[i]);
                break;
            case ".jpg":
                SDL_Surface* currentSurface = SDL_LoadJPG(image_filenames[i]);
                break;
            default:
                SDL_Log("ERROR at file ", image_filenames[i]);
                assert (0 && "Sorry, only .png, .bmp, and .jpg are compatible :c Your image either has the wrong extension or is not supported.");
        }
        */

        if (file_extension == ".png") {
            currentSurface = SDL_LoadPNG(current_filename);
            SDL_Log("aaa");
        } else if (file_extension.c_str() == ".bmp") {
            currentSurface = SDL_LoadBMP(current_filename);
        // } else if (file_extension == ".jpg") {                                       // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            // SDL_Surface* currentSurface = SDL_LoadJPG(current_filename);           // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        } else {
            SDL_Log("file extension: %s", file_extension.c_str());
            SDL_Log("ERROR at file %s", current_filename);
            // assert (0 && "Sorry, only .png, .bmp, and .jpg are compatible :c Your image either has the wrong extension or is not supported.");      // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            assert (0 && "Sorry, only .png, and .bmp are compatible :c Your image either has the wrong extension or is not supported.");               // COMMENTATE   THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        }
        if (currentSurface == nullptr){
            SDL_Log("file extension: %s", file_extension.c_str());
            SDL_Log("ERROR at file %s", current_filename);
		    assert(0 && "ERROR: File not found :c");
	    }

        currentTexture = SDL_CreateTextureFromSurface(your_renderer, currentSurface);
        your_textures.push_back(currentTexture);
    }

    return your_textures;
}
