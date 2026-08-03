#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <cassert>


// #include <bits/stdc++.h>     ---> Maybe needed for c_str() ???

// HUGE credits to Mike Shah (https://www.youtube.com/watch?v=AwAbJeukrqU) since most of this code comes from him,
// and I could have never never never managed to make it work without that tutorial...

// ...

// There will be three optional p

namespace supermotor
{
namespace text
{

class Text{
  private:
    SDL_Texture* my_texture;

  public:

    // Constructor: 3 parameters.
    Text(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text_shown){

        SDL_Surface* textSurface1 = TTF_RenderText_Solid(mFont, text_shown.c_str(), 0, SDL_Color{0, 0, 0, 255});      // White text.

        my_texture = SDL_CreateTextureFromSurface(mRenderer, textSurface1);
        SDL_SetTextureScaleMode(my_texture, SDL_SCALEMODE_NEAREST);        // Also called "nearest neighbour". Suitable for pixel-art textures, like the pixel-art font we are using (no interpolation or antialiasing).

        SDL_DestroySurface(textSurface1);
    }



    // Constructor: 4 parameters.
    Text(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text_shown, std::string filepath){       // filepath here is optional. Just a fallback in case we can't load your font.

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

        Text(mRenderer, mFont, text_shown);
    }


    // Constructor: 2 parameters.
    Text(SDL_Renderer* mRenderer, std::string text_shown){
        TTF_Font* mFont = TTF_OpenFont("../Fonts/Minecraft.ttf", 12.0);
        Text(mRenderer, mFont, text_shown);
    }


    // Getter.
    SDL_Texture* get_texture()  {return my_texture;}

    // Setter.
    void set_texture(SDL_Texture* new_texture) {new_texture = my_texture;}



    // Destructor.
    ~Text(){
        SDL_DestroyTexture(my_texture);
    }
};


}
}
