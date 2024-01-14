#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
void manageKeyDownEvent(SDL_Keycode keyCode)
{
    switch (keyCode)
    {
    case SDLK_q:
        printf("appui q \n");
        break;
    case SDLK_z:
        printf("appui z \n");
        break;
    case SDLK_d:
        printf("appui d \n");
        break;
    case SDLK_s:
        printf("appui s \n");
        break;
    default:
    {
        break;
    }
    }
}