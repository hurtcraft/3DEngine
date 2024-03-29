#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "CONSTANT.hpp"
#include "event.hpp"
#include "player.hpp"
#include "utils.hpp"

void exitWithError(const char *msg);
void drawMap(SDL_Renderer *renderer, const std::vector<std::vector<int>> &map);
void drawFloor(SDL_Renderer *renderer);
void drawCeil(SDL_Renderer *renderer);
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("ERREUR : INIT SDL > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    };
    std::vector<Point3D> cube{
        Point3D{0.0, 0.0, 0.0},
        Point3D{0.0, 1.0, 0.0},
        Point3D{1.0, 1.0, 0.0},
        Point3D{1.0, 0.0, 0.0},

        Point3D{0.0, 0.0, 1.0},
        Point3D{0.0, 1.0, 1.0},
        Point3D{1.0, 1.0, 1.0},
        Point3D{1.0, 0.0, 1.0},
    };

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0)
    {
        exitWithError("CREATION FENETRE + RENDU ECHOUER");
    };
    bool quit = false;
    bool run = true;
    const int facteur = 100;
    int FOV = 100;

    Player p{renderer, "toto", 100, 300, 100};
    std::vector<std::vector<int>> map{
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}};

    int mouseX = 0;
    while (run)
    {

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
        SDL_RenderClear(renderer);
        drawCeil(renderer);
        drawFloor(renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                // manageKeyDownEvent(event.key.keysym.sym);
                p.move(event.key.keysym.sym);

                break;
            case SDL_QUIT:
                run = false;
                break;
            case SDL_MOUSEMOTION:

                mouseX = event.motion.xrel;
                p.updateAngleVision(renderer, mouseX);

            default:
                break;
            }
        }

        // p.drawDirection();
        // p.drawRays();
        p.getRays(map);
        p.drawPlayer();

        drawMap(renderer, map);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void drawFloor(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.w = WIDTH;
    rect.h = HEIGHT / 2;
    rect.x = 0;
    rect.y = HEIGHT / 2;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
    SDL_RenderFillRect(renderer, &rect);
}
void drawCeil(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.w = WIDTH;
    rect.h = HEIGHT / 2;
    rect.x = 0;
    rect.y = 0;

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_RenderFillRect(renderer, &rect);
}
void drawMap(SDL_Renderer *renderer, const std::vector<std::vector<int>> &map)
{
    static SDL_Rect rect;
    rect.h = CELL_SIZE;
    rect.w = CELL_SIZE;
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[0].size(); ++j)
        {
            rect.x = j * CELL_SIZE;
            rect.y = i * CELL_SIZE;
            if (map[i][j] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            else
            {
                // SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
            }

            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void exitWithError(const char *msg)
{
    SDL_Log("ERREUR : %s > %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
