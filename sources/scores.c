#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "file.h"
#include "menu.h"


void getScoresPage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button)
{
    SDL_Surface *background = NULL, *title = NULL, *pseudo = NULL, *text = NULL, *textWhite = NULL, *image = NULL, *quit = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionPseudo = {0}, positionText = {0}, positionTextWhite = {0}, positionImage = {0}, positionQuit = {0};
    SDL_Color colorTitle = {255, 255, 255, 0};
    SDL_Color colorSubTitle = {0, 0, 255, 0};
    SDL_Color colorName = {153, 51, 0, 0};
    SDL_Color colorText = {0, 0, 0, 0};
    SDL_Event event = {0};
    int continued = 1, playerNumber = 0, i = 0, clickQuit = 0, calculateMinutes = 0, calculateSeconds = 0;
    char timeOfGame[6] = {0}, level[5] = {0};
    Winner player[5] = {{{0}}};


    background = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(window->format, 150, 150, 150));
    positionBackground.x = 0;
    positionBackground.y = 0;
    SDL_BlitSurface(background, NULL, window, &positionBackground);
    SDL_FreeSurface(background);

    title = TTF_RenderText_Blended(fontTitle, TITLE, colorTitle);
    positionTitle.x = (window->w / 2) - (title->w / 2);
    positionTitle.y = 8;
    SDL_BlitSurface(title, NULL, window, &positionTitle);
    SDL_FreeSurface(title);

    TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextLarge, "Meilleurs Scores", colorSubTitle);
    positionText.x = (window->w / 2) - (text->w / 2);
    positionText.y = 67;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    playerNumber = getListWinners(player);

    if(playerNumber == 0)
    {
        TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
        text = TTF_RenderText_Blended(fontTextLarge, "Aucun meilleur score n'a été enregistré", colorName);
        positionText.x = (window->w / 2) - (text->w / 2);
        positionText.y = (window->h / 2) - (text->h / 2);
        SDL_BlitSurface(text, NULL, window, &positionText);
        SDL_FreeSurface(text);
    }
    else
    {
        positionImage.x = 13;
        positionImage.y = 127;
        positionText.x = 278;
        positionText.y = 136;

        for(i = 0; i < playerNumber; i++)
        {
            switch(i)
            {
                case 0:
                    image = IMG_Load("images/gold.jpg");
                    break;

                case 1:
                    image = IMG_Load("images/silver.jpg");
                    break;

                case 2:
                    image = IMG_Load("images/bronze.jpg");
                    break;

                default:
                    break;
            }
            SDL_BlitSurface(image, NULL, window, &positionImage);

            TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
            pseudo = TTF_RenderText_Blended(fontTextLarge, player[i].name, colorName);
            positionPseudo.x = 110;
            positionPseudo.y = positionImage.y + ((image->h / 2) - (pseudo->h / 2));
            SDL_BlitSurface(pseudo, NULL, window, &positionPseudo);
            SDL_FreeSurface(pseudo);
            SDL_FreeSurface(image);

            positionImage.y += 80;

            TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
            text = TTF_RenderText_Blended(fontTextSmall, player[i].currentDate, colorText);
            SDL_BlitSurface(text, NULL, window, &positionText);
            SDL_FreeSurface(text);

            TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
            text = TTF_RenderText_Blended(fontTextSmall, "Nombre de coups : ", colorText);
            positionText.y += 17;
            SDL_BlitSurface(text, NULL, window, &positionText);
            positionTextWhite.x = positionText.x + text->w;
            positionTextWhite.y = positionText.y;
            SDL_FreeSurface(text);
            TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
            sprintf(level, "%d", player[i].level);
            textWhite = TTF_RenderText_Blended(fontTextSmall, level, colorTitle);
            SDL_BlitSurface(textWhite, NULL, window, &positionTextWhite);
            SDL_FreeSurface(textWhite);

            calculateMinutes = player[i].elapseTime / 60000;
            calculateSeconds = (player[i].elapseTime % 60000) / 1000;
            if(calculateSeconds < 10)
            {
                sprintf(timeOfGame, "%d:0%d", calculateMinutes, calculateSeconds);
            }
            else
            {
                sprintf(timeOfGame, "%d:%d", calculateMinutes, calculateSeconds);
            }


            TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
            text = TTF_RenderText_Blended(fontTextSmall, "Temps de jeu : ", colorText);
            positionText.y += 17;
            SDL_BlitSurface(text, NULL, window, &positionText);
            positionTextWhite.x = positionText.x + text->w;
            positionTextWhite.y = positionText.y;
            SDL_FreeSurface(text);
            TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
            textWhite = TTF_RenderText_Blended(fontTextSmall, timeOfGame, colorTitle);
            SDL_BlitSurface(textWhite, NULL, window, &positionTextWhite);
            SDL_FreeSurface(textWhite);

            positionText.y += 46;
        }
    }

    quit = IMG_Load("images/return.png");
    positionQuit.x = (window->w / 2) - (quit->w / 2);
    positionQuit.y = 388;
    SDL_BlitSurface(quit, NULL, window, &positionQuit);

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
                if (event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionQuit.x && event.button.x <= (positionQuit.x + quit->w)) && (event.button.y >= positionQuit.y && event.button.y <= (positionQuit.y + quit->h)))
                {
                    SDL_FreeSurface(quit);
                    quit = IMG_Load("images/return1.png");
                    SDL_BlitSurface(quit, NULL, window, &positionQuit);
                    SDL_Flip(window);
                    SDL_FreeSurface(quit);
                    clickQuit = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && clickQuit == 1)
                {
                    quit = IMG_Load("images/return.png");
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

    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
}
