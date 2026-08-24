#ifndef PAUSING_HEADER_FILE
#define PAUSING_HEADER_FILE

#include "screenshots.h"

namespace supermotor
{

/*
// Reminder:
union asset {
    SDL_Surface* surface;
    SDL_Texture* texture;
};
*/


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1280
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 720
#endif


SDL_Rect Background_rect{
    .x = 0,
    .y = 0,
    .w = WINDOW_WIDTH,
    .h = WINDOW_HEIGHT
};



SDL_FRect Background_frect{
    .x = 0.0f,
    .y = 0.0f,
    .w = (float) WINDOW_WIDTH,
    .h = (float) WINDOW_HEIGHT
};






SDL_Surface*  my_cpu_screenshot;                 //  Why, yes, we "pause" by taking a screenshot :3
SDL_Texture*  my_gpu_screenshot;



void pause_init(SDL_Window* my_window, SDL_Renderer* my_renderer) {

    if (my_renderer == nullptr) {
        my_cpu_screenshot = SDL_GetWindowSurface(my_window);
    } else {
        my_cpu_screenshot = SDL_RenderReadPixels(my_renderer, nullptr);
        my_gpu_screenshot = SDL_CreateTextureFromSurface(my_renderer, my_cpu_screenshot);
        SDL_DestroySurface(my_cpu_screenshot);
    }
}



void pause(SDL_Window* my_window, SDL_Renderer* my_renderer, Uint8 opacity = 0x88){

    if (my_renderer == nullptr) {

        SDL_Surface* current_frame = SDL_GetWindowSurface(my_window);
        SDL_BlitSurface(my_cpu_screenshot, nullptr, current_frame, &Background_rect);
        SDL_FillSurfaceRect(current_frame, &Background_rect, (0x00, 0x00, 0x00, opacity));

    } else {

        SDL_RenderTexture(my_renderer, my_gpu_screenshot, nullptr, &Background_frect);

        // ---- PROLOGUE (STORE) ----
        Uint8 current_render_draw_color[4];        // Prevents us from overwriting your current render draw color (https://wiki.libsdl.org/SDL3/SDL_SetRenderDrawColor).
        SDL_GetRenderDrawColor(my_renderer, &current_render_draw_color[0], &current_render_draw_color[1], &current_render_draw_color[2], &current_render_draw_color[3]);

        SDL_BlendMode current_draw_blend_mode;     // Prevents us from overwriting your current blend mode (https://wiki.libsdl.org/SDL3/SDL_SetRenderDrawBlendMode).
        SDL_GetRenderDrawBlendMode(my_renderer, &current_draw_blend_mode);      

        // ---- RENDER ----
        SDL_SetRenderDrawColor(my_renderer, 0x00, 0x00, 0x00, opacity);         // "my_gpu_black_screen".
        SDL_SetRenderDrawBlendMode(my_renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(my_renderer, &Background_frect);

        // ---- EPILOGUE (RESTORE) ----
        SDL_SetRenderDrawColor(my_renderer, current_render_draw_color[0], current_render_draw_color[1], current_render_draw_color[2], current_render_draw_color[3]);    // Restore your previous render draw color.
        SDL_SetRenderDrawBlendMode(my_renderer, current_draw_blend_mode);
    }
}



}
#endif
