#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "menu.h"


void getScoresPage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button)
{
    SDL_Surface *background = NULL, *title = NULL, *text = NULL, *image = NULL, *quit = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionText = {0}, positionImage = {0}, positionQuit = {0};
    SDL_Color colorTitle = {255, 255, 255, 0};
    SDL_Color colorSubTitle = {0, 0, 255, 0};
    SDL_Color colorName = {153, 51, 0, 0};
    SDL_Color colorText = {0, 0, 0, 0};
    SDL_Event event = {0};
    int continued = 1;


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





    // Rien que pour vos yeux


    image = IMG_Load("images/gold.jpg");
    positionImage.x = 13;
    positionImage.y = 127;
    SDL_BlitSurface(image, NULL, window, &positionImage);
    SDL_FreeSurface(image);

    TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextLarge, "SEBASTIEN", colorName);
    positionText.x = 110;
    positionText.y = 151;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Le 16/02/2017 à 08:21", colorText);
    positionText.x = 278;
    positionText.y = 138;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Nombre de coups : ", colorText);
    positionText.x = 278;
    positionText.y = 155;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 155;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "3", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Temps de jeu : ", colorText);
    positionText.x = 278;
    positionText.y = 172;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 172;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "03:42", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    image = IMG_Load("images/silver.jpg");
    positionImage.x = 13;
    positionImage.y = 207;
    SDL_BlitSurface(image, NULL, window, &positionImage);
    SDL_FreeSurface(image);

    TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextLarge, "PATOU", colorName);
    positionText.x = 110;
    positionText.y = 231;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Le 26/01/2017 à 22:28", colorText);
    positionText.x = 278;
    positionText.y = 218;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Nombre de coups : ", colorText);
    positionText.x = 278;
    positionText.y = 235;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 235;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "10", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Temps de jeu : ", colorText);
    positionText.x = 278;
    positionText.y = 252;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 252;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "115:42", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    image = IMG_Load("images/bronze.jpg");
    positionImage.x = 13;
    positionImage.y = 287;
    SDL_BlitSurface(image, NULL, window, &positionImage);
    SDL_FreeSurface(image);

    TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextLarge, "FIDJI", colorName);
    positionText.x = 110;
    positionText.y = 311;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Le 06/12/2016 à 05:02", colorText);
    positionText.x = 278;
    positionText.y = 298;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Nombre de coups : ", colorText);
    positionText.x = 278;
    positionText.y = 315;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 315;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "10", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "Temps de jeu : ", colorText);
    positionText.x = 278;
    positionText.y = 332;
    SDL_BlitSurface(text, NULL, window, &positionText);
    positionText.x = positionText.x + text->w;
    positionText.y = 332;
    SDL_FreeSurface(text);
    TTF_SetFontStyle(fontTextSmall, TTF_STYLE_NORMAL);
    text = TTF_RenderText_Blended(fontTextSmall, "351:28", colorTitle);
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    // Finn du juste pour vos yeux










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

            default:
                break;
        }
    }
    SDL_FreeSurface(quit);

    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
}
