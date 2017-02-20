#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "menu.h"


void getGamePage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button)
{
    SDL_Surface *background = NULL, *board = NULL, *about = NULL, *sound_on = NULL;
    SDL_Rect positionBackground = {0}, positionBoard = {0}, positionAbout = {0}, positionSound_on = {0};
    SDL_Event event = {0};
    int continued = 1;


    background = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(window->format, 150, 150, 150));
    positionBackground.x = 0;
    positionBackground.y = 0;
    SDL_BlitSurface(background, NULL, window, &positionBackground);
    SDL_Flip(window);
    SDL_FreeSurface(background);

    board = IMG_Load("images/board.png");
    positionBoard.x = (window->w / 2) - (board->w / 2);
    positionBoard.y = 7;
    SDL_BlitSurface(board, NULL, window, &positionBoard);
    SDL_Flip(window);
    SDL_FreeSurface(board);

    about = IMG_Load("images/about.png");
    positionAbout.x = 17;
    positionAbout.y = 411;
    SDL_BlitSurface(about, NULL, window, &positionAbout);
    SDL_FreeSurface(about);

    if(sound)
    {
        sound_on = IMG_Load("images/sound_on.png");
    }
    else
    {
        sound_on = IMG_Load("images/sound_off.png");
    }
    positionSound_on.x = (window->w - 17) - sound_on->w;
    positionSound_on.y = 406;
    SDL_BlitSurface(sound_on, NULL, window, &positionSound_on);
    SDL_FreeSurface(sound_on);

    SDL_Flip(window);

    while(continued)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continued = 0;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continued = 0;
                }
                break;

            default:
                break;
        }
    }

    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
}
