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
    SDL_Surface *background = NULL, *title = NULL, *text = NULL, *frame = NULL, *inputLetter = NULL, *keyLetter = NULL, *validate = NULL, *cancel = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionText = {0}, positionFrame = {0}, positionInputLetter = {0}, positionKeyLetter = {0}, positionValidate = {0}, positionCancel = {0};
    SDL_Color colorTitle = {255, 255, 255, 0}, colorSubTitle = {0, 0, 255, 0}, colorLetter = {0, 0, 0, 0};
    SDL_Event event = {0};
    TTF_Font *fontTextXLarge = NULL;
    FMOD_SOUND *clickLetter = NULL;
    int i = 0, continued = 1, letterSelected = 0, currentLetter = 0, clickKey = 0, clickValidate = 0, clickCancel = 0, clickTheEnd = 0;
    char playerName[] = "_    _    _    _    _    _    _    _", pictName[15] = {0}, alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    fontTextXLarge = TTF_OpenFont("fonts/letters.ttf", 28);
    FMOD_System_CreateSound(system, "sounds/letters.wav", FMOD_CREATESAMPLE, 0, &clickLetter);

    while(continued)
    {
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

        TTF_SetFontStyle(fontTextXLarge, TTF_STYLE_NORMAL);
        inputLetter = TTF_RenderText_Blended(fontTextXLarge, playerName, colorLetter);
        positionInputLetter.x = positionFrame.x + (frame->w / 2) - (inputLetter->w / 2);
        positionInputLetter.y = positionFrame.y + (frame->h / 2) - (inputLetter->h / 2);
        SDL_BlitSurface(inputLetter, NULL, window, &positionInputLetter);
        SDL_FreeSurface(inputLetter);

        SDL_FreeSurface(frame);

        positionKeyLetter.x = (window->w / 2) - 196;
        positionKeyLetter.y = 280;
        for(i = 0; i < 26; i++)
        {
            sprintf(pictName, "images/%c.png", alphabet[i]);
            keyLetter = IMG_Load(pictName);
            SDL_BlitSurface(keyLetter, NULL, window, &positionKeyLetter);
            SDL_FreeSurface(keyLetter);
            positionKeyLetter.x += 40;
            if(i == 9 || i == 19)
            {
                positionKeyLetter.x = (window->w / 2) - 196;
                positionKeyLetter.y += 40;
            }
        }

        if(clickKey)
        {
            sprintf(pictName, "images/%c1.png", alphabet[letterSelected]);
            keyLetter = SDL_CreateRGBSurface(SDL_HWSURFACE, 40, 40, 32, 0, 0, 0, 0);
            SDL_FillRect(keyLetter, NULL, SDL_MapRGB(window->format, 150, 150, 150));
            positionKeyLetter.x = ((window->w / 2) - 196) + ((event.button.x - ((window->w / 2) - 196)) / 40) * 40;
            positionKeyLetter.y = 280 + ((event.button.y - 280) / 40) * 40;
            SDL_BlitSurface(keyLetter, NULL, window, &positionKeyLetter);
            SDL_FreeSurface(keyLetter);
            keyLetter = IMG_Load(pictName);
            positionKeyLetter.x++;
            positionKeyLetter.y++;
            SDL_BlitSurface(keyLetter, NULL, window, &positionKeyLetter);
            SDL_FreeSurface(keyLetter);
        }

        if(clickCancel)
        {
            cancel = IMG_Load("images/delete1.png");
            positionCancel.x = ((window->w / 2) - 196) + (40 * 7) + 1;
            positionCancel.y = 360 + 1;
        }
        else
        {
            cancel = IMG_Load("images/delete.png");
            positionCancel.x = ((window->w / 2) - 196) + (40 * 7);
            positionCancel.y = 360;
        }
        SDL_BlitSurface(cancel, NULL, window, &positionCancel);
        SDL_FreeSurface(cancel);

        if(clickValidate)
        {
            validate = IMG_Load("images/enter_name1.png");
            positionValidate.x = ((window->w / 2) - 196) + (40 * 8) + 1;
            positionValidate.y = 360 + 1;
        }
        else
        {
            validate = IMG_Load("images/enter_name.png");
            positionValidate.x = ((window->w / 2) - 196) + (40 * 8);
            positionValidate.y = 360;
        }
        SDL_BlitSurface(validate, NULL, window, &positionValidate);
        SDL_FreeSurface(validate);

        SDL_Flip(window);


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
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if((clickKey == 0) && ((event.button.x >= ((window->w / 2) - 196) && event.button.x <= (((window->w / 2) - 196) + 392) && event.button.y >= 280 && event.button.y <= 280 + 32) || (event.button.x >= ((window->w / 2) - 196) && event.button.x <= (((window->w / 2) - 196) + 392) && event.button.y >= 320 && event.button.y <= 320 + 32) || (event.button.x >= ((window->w / 2) - 196) && event.button.x <= (((window->w / 2) - 196) + 232) && event.button.y >= 360 && event.button.y <= 360 + 32)))
                    {
                        if((event.button.x >= ((window->w / 2) - 196) && event.button.x <= (((window->w / 2) - 196) + 32) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 40) && event.button.x <= (((window->w / 2) - 196) + 72) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 80) && event.button.x <= (((window->w / 2) - 196) + 112) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 120) && event.button.x <= (((window->w / 2) - 196) + 152) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 160) && event.button.x <= (((window->w / 2) - 196) + 192) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 200) && event.button.x <= (((window->w / 2) - 196) + 232) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 240) && event.button.x <= (((window->w / 2) - 196) + 272) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 280) && event.button.x <= (((window->w / 2) - 196) + 312) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 320) && event.button.x <= (((window->w / 2) - 196) + 352) && event.button.y >= 280 && event.button.y <= 392) || (event.button.x >= (((window->w / 2) - 196) + 360) && event.button.x <= (((window->w / 2) - 196) + 392) && event.button.y >= 280 && event.button.y <= 392))
                        {
                            if(sound)
                            {
                                FMOD_System_PlaySound(system, 1, clickLetter, 0, NULL);
                            }

                            letterSelected = (((event.button.x - ((window->w / 2) - 196)) / 40) + (((event.button.y - 280) / 40) * 10));

                            clickKey = 1;

                            if(currentLetter <= 35)
                            {
                                playerName[currentLetter] = toupper(alphabet[letterSelected]);
                                currentLetter += 5;
                            }
                        }
                    }
                    else if(clickCancel == 0 && event.button.x >= positionCancel.x && event.button.x <= (positionCancel.x + 32) && event.button.y >= positionCancel.y && event.button.y <= (positionCancel.y + 32))
                    {
                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }

                        clickCancel = 1;

                        if(currentLetter >= 5)
                        {
                            currentLetter -= 5;
                            playerName[currentLetter] = '_';
                        }
                    }
                    else if(clickValidate == 0 && event.button.x >= positionValidate.x && event.button.x <= (positionValidate.x + 32) && event.button.y >= positionValidate.y && event.button.y <= (positionValidate.y + 32))
                    {
                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }

                        clickValidate = 1;

                        setBestScore(shot, elapsedTime, actualDate, playerName);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(clickCancel == 1)
                    {
                        clickCancel = 0;
                    }
                    else if(clickValidate == 1)
                    {
                        clickValidate = 0;
                        clickTheEnd = 1;
                        continued = 0;
                    }
                    else if(clickKey == 1)
                    {
                        clickKey = 0;
                    }
                }
                break;

            default:
                break;
        }
    }

    FMOD_Sound_Release(clickLetter);
    TTF_CloseFont(fontTextXLarge);

    if(clickTheEnd)
    {
        getScoresPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }
    else
    {
        getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }
}
