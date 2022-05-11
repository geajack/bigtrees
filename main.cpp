#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>

#include "trees.cpp"

const int WINDOW_WIDTH  = 1000;
const int WINDOW_HEIGHT = 1000;

typedef Uint32 (*PixelBuffer)[WINDOW_HEIGHT];

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window *window = SDL_CreateWindow("New SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    PixelBuffer pixels = (PixelBuffer) window_surface->pixels;

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(surface);

    Uint32 white = SDL_MapRGBA(window_surface->format, 255, 255, 255, 255);

    const int DEPTH = 18;
    BinaryTree tree(DEPTH);
    BinaryTreePath path(DEPTH);
    MaximinSolver solver(DEPTH);
    int score = solver.solve(&tree, &path);

    int tile_size = 40;
    int center_x = WINDOW_WIDTH / 2;

    SDL_Rect tile;
    tile.x = 0;
    tile.y = 0;
    tile.w = tile_size;
    tile.h = tile_size;

    unsigned long t = 0;

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

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int n = 1; n <= DEPTH + 1; n++)
        {
            int x = center_x - (tile_size / 2) * n;
            int y = WINDOW_HEIGHT - n * tile_size - 100;
            tile.x = x;
            tile.y = y;
            for (int i = 0; i < n; i++)
            {
                SDL_RenderFillRect(renderer, &tile);
                tile.x += tile_size;
            }
        }

        MaximinState state = solver.history[t];
        int digital_sum = 0;
        for (int digit_index = 0; digit_index < state.depth; digit_index++)
        {
            digital_sum += ((state.path & (1 << digit_index)) > 0);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int n = state.depth + 1;
        int i = digital_sum;
        tile.x = center_x - (tile_size / 2) * n + i * tile_size;
        tile.y = WINDOW_HEIGHT - n * tile_size - 100;
        SDL_RenderFillRect(renderer, &tile);

        t += 1;

        if (t >= solver.t)
        {
            t = solver.t;
        }

        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface(window);
        
        SDL_Delay(1000 / 60);
    }

    SDL_Quit();

    return 0;
}