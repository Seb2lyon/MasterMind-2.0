#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "menu.h"
#include "game.h"


void getAboutPage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button, int referer)
{
    SDL_Surface *background = NULL, *title = NULL, *created = NULL, *creator = NULL, *message1 = NULL, *message2 = NULL, *quit = NULL, *copyright = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionCreated = {0}, positionCreator = {0}, positionMessage1 = {0}, positionMessage2 = {0}, positionQuit = {0}, positionCopyright = {0};
    SDL_Color color1 = {0, 0, 0, 0}, color2 = {128, 0, 0, 0};
    SDL_Event event = {0};
    int continued = 1, clickQuit = 0;


    background = IMG_Load("images/about.gif");
    positionBackground.x = (window->w / 2) - (background->w / 2);
    positionBackground.y = (window->h / 2) - (background->h / 2);
    SDL_BlitSurface(background, NULL, window, &positionBackground);
    SDL_FreeSurface(background);

    title = IMG_Load("images/about_title.png");
    positionTitle.x = (window->w / 2) - (title->w / 2);
    positionTitle.y = positionBackground.y + 31;
    SDL_BlitSurface(title, NULL, window, &positionTitle);
    SDL_FreeSurface(title);

    TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
    created = TTF_RenderText_Blended(fontTextNormal, "Création et développement", color1);
    positionCreated.x = (window->w / 2) - (created->w / 2);
    positionCreated.y = positionBackground.y + 107;
    SDL_BlitSurface(created, NULL, window, &positionCreated);
    SDL_FreeSurface(created);

    TTF_SetFontStyle(fontTextNormal, TTF_STYLE_BOLD);
    creator = TTF_RenderText_Blended(fontTextNormal, "Seb2lyon", color1);
    positionCreator.x = (window->w / 2) - (creator->w / 2);
    positionCreator.y = positionBackground.y + 131;
    SDL_BlitSurface(creator, NULL, window, &positionCreator);
    SDL_FreeSurface(creator);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_ITALIC);
    message1 = TTF_RenderText_Blended(fontTextSmall, "Pour Patricia", color1);
    positionMessage1.x = (window->w / 2) - (message1->w / 2);
    positionMessage1.y = positionBackground.y + 159;
    SDL_BlitSurface(message1, NULL, window, &positionMessage1);
    SDL_FreeSurface(message1);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_ITALIC);
    message2 = TTF_RenderText_Blended(fontTextSmall, "mon Amour, mon Bonheur, ma Chance", color1);
    positionMessage2.x = (window->w / 2) - (message2->w / 2);
    positionMessage2.y = positionBackground.y + 175;
    SDL_BlitSurface(message2, NULL, window, &positionMessage2);
    SDL_FreeSurface(message2);

    quit = IMG_Load("images/about_return.png");
    positionQuit.x = (window->w / 2) - (quit->w / 2);
    positionQuit.y = positionBackground.y + 210;
    SDL_BlitSurface(quit, NULL, window, &positionQuit);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
    copyright = TTF_RenderText_Blended(fontTextSmall, "07/07/2020 - version 1.1", color2);
    positionCopyright.x = (window->w / 2) - (copyright->w / 2);
    positionCopyright.y = positionBackground.y + 262;
    SDL_BlitSurface(copyright, NULL, window, &positionCopyright);
    SDL_FreeSurface(copyright);

    SDL_Flip(window);

    while(continued)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continued = 0;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionQuit.x && event.button.x <= (positionQuit.x + quit->w)) && (event.button.y >= positionQuit.y && event.button.y <= (positionQuit.y + quit->h)))
                {
                    SDL_FreeSurface(quit);
                    quit = IMG_Load("images/about_return1.png");
                    SDL_BlitSurface(quit, NULL, window, &positionQuit);
                    SDL_FreeSurface(quit);
                    SDL_Flip(window);
                    clickQuit = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT && clickQuit == 1)
                {
                    quit = IMG_Load("images/about_return.png");
                    SDL_BlitSurface(quit, NULL, window, &positionQuit);
                    SDL_Flip(window);
                    clickQuit = 0;

                    continued = 0;
                }


            default:
                break;
        }
    }

    SDL_FreeSurface(quit);

    if(referer == 1)
    {
        getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }
}
