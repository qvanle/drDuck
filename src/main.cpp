#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>

bool status = 1;
SDL_Window* window;
int WIDTH = 960;
int HEIGHT = 540;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Dr Duck", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, 
        HEIGHT, 
        SDL_WINDOW_SHOWN
   );
}

void Action()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            status = 0;
        }
    }
}

void shutdown()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
}

int main()
{
    init();
    while(status)
        Action();

    shutdown();

    return 0;
}
