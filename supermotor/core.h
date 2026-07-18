// Batch rendering implementations (should) go here.

// Input:  Your renderer and your filenames (as C strings)
// Output: A vector with your textures ()

// NOTE: Only accepts .png, .jpg, and .bmp file formats.
//       (If you want other file formats, you can ask me to implement one, or look for another tool yourself, such as this one ---> https://wiki.libsdl.org/SDL3_image/FrontPage)
//       (for more info, read here ---> https://wiki.libsdl.org/SDL3/CategorySurface)


#include <bits/stdc++.h>
#include <vector>
#include <SDL3/SDL.h>

#include <cassert>



// Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
// (DO NOT run this on your game loop)
std::vector<SDL_Texture*> generate_textures(SDL_Renderer* your_renderer, std::string image_filenames[], uint64_t number_of_files){
    
    std::vector<SDL_Texture*> your_textures;

    for (int i = 0; i < number_of_files; i++){
        SDL_Texture* currentTexture;

        std::string emanelif_tnerruc = image_filenames[i];        // Trying to do an implicit cast over here...
        std::reverse((emanelif_tnerruc).begin(), (emanelif_tnerruc).end());     // .emanelif desreveR
        
        std::string file_extension = emanelif_tnerruc[0] + emanelif_tnerruc[1] + emanelif_tnerruc[2] + emanelif_tnerruc[3];

        std::reverse((emanelif_tnerruc).begin(), (emanelif_tnerruc).end());
        emanelif_tnerruc = emanelif_tnerruc.c_str();


        SDL_Surface* currentSurface;
        
        char* current_filename = image_filenames[i].c_str();

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
            SDL_Surface* currentSurface = SDL_LoadPNG(current_filename);
        } else if (file_extension == ".bmp") {
            SDL_Surface* currentSurface = SDL_LoadBMP(current_filename);
        // } else if (file_extension == ".jpg") {                                       // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            // SDL_Surface* currentSurface = SDL_LoadJPG(current_filename);           // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        } else {
            SDL_Log("ERROR at file %s", current_filename);
            // assert (0 && "Sorry, only .png, .bmp, and .jpg are compatible :c Your image either has the wrong extension or is not supported.");      // UNCOMMENTATE THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
            assert (0 && "Sorry, only .png, and .bmp are compatible :c Your image either has the wrong extension or is not supported.");               // COMMENTATE   THIS IN VERSION > 3.6.0 (we are at 3.4.X at the time of me coding this)
        }

        currentTexture = SDL_CreateTextureFromSurface(your_renderer, currentSurface);
        your_textures.push_back(currentTexture);
    }

    return your_textures;
}
