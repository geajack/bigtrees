#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>

const int WINDOW_WIDTH  = 1000;
const int WINDOW_HEIGHT = 1000;

typedef Uint32 (*PixelBuffer)[WINDOW_HEIGHT];

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window *window = SDL_CreateWindow("New SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    PixelBuffer pixels = (PixelBuffer) window_surface->pixels;

    Uint32 white = SDL_MapRGBA(window_surface->format, 255, 255, 255, 255);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                quit = 1;
                break;
            }
        }

        int y = 200;
        for (int x = 300 - 128; x <= 300 + 128; x++)
        {
            pixels[y][x] = white;
        }

        SDL_UpdateWindowSurface(window);
        
        SDL_Delay(1000 / 60);
    }

    SDL_Quit();

    return 0;
}