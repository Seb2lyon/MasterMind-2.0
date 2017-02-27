#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "file.h"
#include "scores.h"
#include "menu.h"


void getNamePage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button, int elapsedTime, int shot, int actualDate)
{
    SDL_Surface *background = NULL, *title = NULL, *text = NULL, *frame = NULL, *inputLetter = NULL, *letter = NULL, *validate = NULL, *cancel = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionText = {0}, positionFrame = {0}, positionInputLetter = {0}, positionLetter = {0}, positionValidate = {0}, positionCancel = {0};
    SDL_Color colorTitle = {255, 255, 255, 0}, colorSubTitle = {0, 0, 255, 0}, colorLetter = {0, 0, 0, 0};
    SDL_Event event = {0};
    TTF_Font *fontTextXLarge = NULL;
    int i = 0, continued = 1;
    char playerName[] = "________", inputName[] = "_ ", pictName[7] = {0}, alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    fontTextXLarge = TTF_OpenFont("fonts/letters.ttf", 28);

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
    text = TTF_RenderText_Blended(fontTextLarge, "Entrez votre nom :", colorSubTitle);
    positionText.x = (window->w / 2) - (text->w / 2);
    positionText.y = 96;
    SDL_BlitSurface(text, NULL, window, &positionText);
    SDL_FreeSurface(text);

    frame = IMG_Load("images/name.png");
    positionFrame.x = (window->w / 2) - (frame->w / 2);
    positionFrame.y = 146;
    SDL_BlitSurface(frame, NULL, window, &positionFrame);

    positionInputLetter.x = positionFrame.x + 30;
    for(i = 0; i < 8; i++)
    {
        sprintf(inputName, "%c ", playerName[i]);
        inputLetter = TTF_RenderText_Blended(fontTextXLarge, inputName, colorLetter);
        positionInputLetter.y = positionFrame.y + (frame->h / 2) - (inputLetter->h / 2);
        SDL_BlitSurface(inputLetter, NULL, window, &positionInputLetter);
        SDL_FreeSurface(inputLetter);
        positionInputLetter.x += 40;
    }

    SDL_FreeSurface(frame);

    positionLetter.x = (window->w / 2) - 196;
    positionLetter.y = 293;
    for(i = 0; i < 26; i++)
    {
        sprintf(pictName, "images/%c.png", alphabet[i]);
        letter = IMG_Load(pictName);
        SDL_BlitSurface(letter, NULL, window, &positionLetter);
        SDL_FreeSurface(letter);
        positionLetter.x += 40;
        if(i == 9 || i == 19)
        {
            positionLetter.x = (window->w / 2) - 196;
            positionLetter.y += 40;
        }
    }

    cancel = IMG_Load("images/delete.png");
    positionCancel.x = positionLetter.x + 40;
    positionCancel.y = positionLetter.y;
    SDL_BlitSurface(cancel, NULL, window, &positionCancel);
    SDL_FreeSurface(cancel);

    validate = IMG_Load("images/enter_name.png");
    positionValidate.x = positionLetter.x + 80;
    positionValidate.y = positionLetter.y;
    SDL_BlitSurface(validate, NULL, window, &positionValidate);
    SDL_FreeSurface(validate);

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

    TTF_CloseFont(fontTextXLarge);

    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
}
