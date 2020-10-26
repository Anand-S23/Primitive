#include <SDL.h> 
#include "..\primitive.h"

bool Running = true; 

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Test", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          640, 480, 0); 

    if (window)
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

        if (renderer)
        {
            while (Running)
            {
                SDL_Event event; 

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        Running = false; 
                    }
                }

                Primitive_DrawFilledTriangle(renderer, 10, 10, 200, 50, 100, 100, P_Color(0, 255, 255, 255));

                SDL_RenderPresent(renderer); 
            }
        }
        else
        {
            // TODO: Error Handling
        }
    }
    else 
    {
        // TODO: Error Handling
    }

    SDL_Quit(); 
    return 0; 
}