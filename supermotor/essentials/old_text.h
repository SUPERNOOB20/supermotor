#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <cassert>


#include <vector>

// #include <bits/stdc++.h>     ---> Maybe needed for c_str() ???

// HUGE credits to Mike Shah (https://www.youtube.com/watch?v=AwAbJeukrqU) since most of this code comes from him,
// and I could have never never never managed to make it work without that tutorial...

// ...

// There will be four optional params - size, colour, font, filename.

// Avoids nullptr
// Inefficient. Change with arrays if you can... e.e

std::vector<SDL_Texture> my_texts;


SDL_Texture* gay_fun(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text){

    SDL_Surface* textSurface69 = TTF_RenderText_Solid(mFont, text.c_str(), 0, SDL_Color{0, 0, 0, 255});      // White text.

    SDL_Texture* my_gay_texture = SDL_CreateTextureFromSurface(mRenderer, textSurface69);
    SDL_SetTextureScaleMode(my_gay_texture, SDL_SCALEMODE_NEAREST);        // Also called "nearest neighbour". Suitable for pixel-art textures, like the pixel-art font we are using (no interpolation or antialiasing).

    SDL_DestroySurface(textSurface69);

    // my_texts.push_back(*my_gay_texture);

    SDL_Log("sizeof my GAY AF texture: %ld", sizeof(*my_gay_texture));

    return my_gay_texture;
}


// SDL_Texture* my_texture;


/*
namespace supermotor
{
namespace text
{
*/



    // Function overloading: 3 parameters.
    SDL_Texture* text_fun(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text_shown){

        SDL_Texture* my_texture;

        SDL_Surface* textSurface1 = TTF_RenderText_Solid(mFont, text_shown.c_str(), 0, SDL_Color{0, 0, 0, 255});      // White text.

        my_texture = SDL_CreateTextureFromSurface(mRenderer, textSurface1);
        SDL_SetTextureScaleMode(my_texture, SDL_SCALEMODE_NEAREST);        // Also called "nearest neighbour". Suitable for pixel-art textures, like the pixel-art font we are using (no interpolation or antialiasing).

        SDL_DestroySurface(textSurface1);

        // my_texts.push_back(*my_texture);


        if (my_texture == nullptr){
            SDL_Log("%s%s%d", __TIME__, " Warning: No texture found! ", __LINE__);
        }

        SDL_Texture* my_allocated_texture = (SDL_Texture*) malloc(sizeof(my_texture));

        my_allocated_texture = my_texture;

        if (my_allocated_texture == nullptr){
            SDL_Log("%s%s%d", __TIME__, " Warning: We found your texture, but malloc() couldn't allocate it! ", __LINE__);
        }

        return my_allocated_texture;
    }



    // Function overloading: 4 parameters.
    SDL_Texture* text_fun(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text_shown, std::string filepath){       // filepath here is optional. Just a fallback in case we can't load your font.

        if(mFont == nullptr){
            SDL_Log("Warning: Couldn't find your fond file :c");
            SDL_Log("Attempting fallback procedure from given filepath. Hang on tight...");
        }
        
        mFont = TTF_OpenFont(filepath.c_str(), 12.0);
        
        if(mFont == nullptr){
            SDL_Log("ERROR: Fallback procedure failed D:");
            SDL_Log("Shutting down...");
            SDL_Log("\n");
            assert(0 && "ERROR: Font file not found :c");
        }

        return text_fun(mRenderer, mFont, text_shown);
    }


    // Function overloading: 2 parameters.
    SDL_Texture* text_fun(SDL_Renderer* mRenderer, std::string text_shown){
        TTF_Font* mFont = TTF_OpenFont("../Fonts/Minecraft.ttf", 12.0);
        return text_fun(mRenderer, mFont, text_shown);
    }

    /*
    // Destructor.
    ~Text(){
        SDL_DestroyTexture(my_texture);
    }
    */

/*
}
}
*/
