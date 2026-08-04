#ifndef TEXT_HEADER_FILE
#define TEXT_HEADER_FILE


#define FONT_SIZE 72.0f




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



namespace supermotor
{
namespace text
{

    // Function overloading: 3 parameters.
    SDL_Texture* make_text(SDL_Renderer* mRenderer, TTF_Font* mFont, const char* text){

        SDL_Texture* my_texture;

        SDL_Surface* textSurface1 = TTF_RenderText_Solid(mFont, text, 0, SDL_Color{255, 255, 255, 255});      // White text.

        my_texture = SDL_CreateTextureFromSurface(mRenderer, textSurface1);
        SDL_DestroySurface(textSurface1);
        SDL_SetTextureScaleMode(my_texture, SDL_SCALEMODE_NEAREST);        // Also called "nearest neighbour". Suitable for pixel-art textures, like the pixel-art font we are using (no interpolation or antialiasing).
        // SDL_SetTextureScaleMode(my_texture, SDL_SCALEMODE_LINEAR);



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
    SDL_Texture* make_text(SDL_Renderer* mRenderer, TTF_Font* mFont, const char* text_shown, std::string filepath){       // filepath here is optional. Just a fallback in case we can't load your font.

        if(mFont == nullptr){
            SDL_Log("Warning: Couldn't find your fond file :c");
            SDL_Log("Attempting fallback procedure from given filepath. Hang on tight...");
        }
        
        mFont = TTF_OpenFont(filepath.c_str(), FONT_SIZE);
        
        if(mFont == nullptr){
            SDL_Log("ERROR: Fallback procedure failed D:");
            SDL_Log("Shutting down...");
            SDL_Log("\n");
            assert(0 && "ERROR: Font file not found :c");
        }

        return make_text(mRenderer, mFont, text_shown);
    }


    // Function overloading: 2 parameters.
    SDL_Texture* make_text(SDL_Renderer* mRenderer, const char* text_shown){
        TTF_Font* mFont = TTF_OpenFont("./Fonts/Minecraft.ttf", FONT_SIZE);
        return make_text(mRenderer, mFont, text_shown);
    }


    // If you want to optimise this, you can probably implement this with SDL_Texture** instead of std::vector<SDL_Texture*>.
    std::vector<SDL_Texture*> make_texts(SDL_Renderer* mRenderer, std::string* texts_shown, Uint64 len){
        std::vector<SDL_Texture*> texts = {};
        texts.reserve(len);

        SDL_Log("texts len: %ld", texts.size());

        for (int i = 0; i < len; i++){
            std::string current_text = texts_shown[i];

            SDL_Texture* current_texture = make_text(mRenderer, current_text.c_str());

            SDL_Log("number of t: %d", i);

            texts.push_back(current_texture);
        }

        SDL_Log("texts len: %ld", texts.size());

        return texts;
    }

    /*
    // Destructor.
    ~Text(){
        SDL_DestroyTexture(my_texture);
    }
    */


}
}




#endif
