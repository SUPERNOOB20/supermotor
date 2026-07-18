// Batch rendering implementations (should) go here.

// Input:  Your renderer and your filenames (as C strings)
// Output: A vector with your textures ()

// NOTE: Only accepts .png, .jpg, and .bmp file formats.
//       (If you want other file formats, you can ask me to implement one, or look for another tool yourself, such as this one ---> https://wiki.libsdl.org/SDL3_image/FrontPage)
//       (for more info, read here ---> https://wiki.libsdl.org/SDL3/CategorySurface)



#include <vector>
#include <SDL3/SDL.h>

#include <cassert>



// Run ONLY ONCE, at startup (or during a loading screen when changing scenes, for example)
// (DO NOT run this on your game loop)
std::vector<SDL_Texture> generate_textures(SDL_Renderer your_renderer, const char* image_filenames[]){
    
    std::vector your_textures;

    for (int i = 0; sizeof(image_filenames[]); i++){
        SDL_Texture* currentTexture;

        std::string emanelif = reverse(image_filename[i].begin(), image_filename[i].end());     // .emanelif desreveR
        

        SDL_Surface* currentSurface;
        switch file_extension{
            case ".png":
                SDL_Surface* currentSurface = SDL_LoadPNG(image_filename[i]);
                break;
            case ".bmp":
                SDL_Surface* currentSurface = SDL_LoadBMP(image_filename[i]);
                break;
            case ".jpg":
                SDL_Surface* currentSurface = SDL_LoadJPG(image_filename[i]);
                break;
            default:
                SDL_Log("ERROR at file ", image_filename[i]);
                assert (0 && "Sorry, only .png, .bmp, and .jpg are compatible :c Your image either has the wrong extension or is not supported.");
                break;
        }

        currentTexture = SDL_CreateTextureFromSurface(mRenderer, currentSurface);
        your_textures.push(currentTexture);

    return your_textures;
}
