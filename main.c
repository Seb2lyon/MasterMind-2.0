/*------------------------------------*
 *    MasterMind 2.0 - version 0.1    *
 *   Created and coded by Seb2lyon    *
 *   from 02/10/2017 to 03/01/2017    *
 *  dedicated to my love : Patricia   *
 *             ENJOY ;)               *
 *------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "menu.h"

int main(int argc, char *args[])
{
    SDL_Surface *window = NULL, *background = NULL, *element = NULL;
    SDL_Rect positionBackground = {0}, positionElement = {0};
    SDL_Color colorTitle = {255, 255, 255, 0};
    SDL_Event event = {0};
    TTF_Font *fontTitle = NULL, *fontTextLarge = NULL, *fontTextNormal = NULL, *fontTextSmall = NULL;
    FMOD_SYSTEM *system = NULL;
    FMOD_SOUND *button = NULL;
    int continued = 1, click = 0, sound = 1;


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);

    window = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("MasterMind 2.0", NULL);
    SDL_WM_SetIcon(IMG_Load("images/icon.png"), NULL);

    FMOD_System_CreateSound(system, "sounds/button.mp3", FMOD_CREATESAMPLE, 0, &button);

    fontTitle = TTF_OpenFont("fonts/title.ttf", 25);
    fontTextLarge = TTF_OpenFont("fonts/letters.ttf", 25);
    fontTextNormal = TTF_OpenFont("fonts/letters.ttf", 19);
    fontTextSmall = TTF_OpenFont("fonts/letters.ttf", 17);

    background = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(window->format, 34, 33, 41));
    positionBackground.x = 0;
    positionBackground.y = 0;
    SDL_BlitSurface(background, NULL, window, &positionBackground);
    SDL_FreeSurface(background);

    element = IMG_Load("images/mastermind.jpg");
    positionElement.x = (window->w / 2) - (element->w / 2);
    positionElement.y = 0;
    SDL_BlitSurface(element, NULL, window, &positionElement);
    SDL_FreeSurface(element);

    element = TTF_RenderText_Blended(fontTitle, TITLE, colorTitle);
    positionElement.x = (window->w / 2) - (element->w / 2);
    positionElement.y = 366;
    SDL_BlitSurface(element, NULL, window, &positionElement);
    SDL_FreeSurface(element);

    element = IMG_Load("images/enter.png");
    positionElement.x = (window->w / 2) - (element->w / 2);
    positionElement.y = 411;
    SDL_BlitSurface(element, NULL, window, &positionElement);

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

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionElement.x && event.button.x <= (positionElement.x + element->w)) && (event.button.y >= positionElement.y && event.button.y <= (positionElement.y + element->h)))
                {
                    SDL_FreeSurface(element);
                    element = IMG_Load("images/enter1.png");
                    SDL_BlitSurface(element, NULL, window, &positionElement);
                    SDL_Flip(window);
                    click = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT && click == 1)
                {
                    SDL_FreeSurface(element);
                    element = IMG_Load("images/enter.png");
                    SDL_BlitSurface(element, NULL, window, &positionElement);
                    SDL_Flip(window);
                    SDL_FreeSurface(element);
                    click = 0;

                    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);

                    continued = 0;
                }
                break;

            default:
                break;
        }
    }

    FMOD_Sound_Release(button);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontTextLarge);
    TTF_CloseFont(fontTextNormal);
    TTF_CloseFont(fontTextSmall);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
