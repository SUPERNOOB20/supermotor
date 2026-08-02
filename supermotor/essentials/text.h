#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace supermotor
{
namespace text
{

class Text{
  private:
    SDL_Texture* my_texture;

  public:
    // Constructor.
    Text(SDL_Renderer* mRenderer, TTF_Font* mFont, std::string text_shown){

        SDL_Surface* textSurface1 = TTF_RenderText_Solid(mFont, text_shown.c_str(), 0, SDL_Color{0, 0, 0, 255});      // White text.

        my_texture = SDL_CreateTextureFromSurface(mRenderer, textSurface1);
        SDL_SetTextureScaleMode(my_texture, SDL_SCALEMODE_NEAREST);        // Also called "nearest neighbour". Suitable for pixel-art textures, like the pixel-art font we are using (no interpolation or antialiasing).

        SDL_DestroySurface(textSurface1);
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
