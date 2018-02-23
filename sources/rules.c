#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "menu.h"


void getRulesPage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button, int referer)
{
    SDL_Surface *background = NULL, *title = NULL, *page = NULL, *text = NULL, *image = NULL, *quit = NULL, *left = NULL, *right = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionPage = {0}, positionText = {0}, positionImage = {0}, positionQuit = {0}, positionLeft = {0}, positionRight = {0};
    SDL_Color colorTitle = {255, 255, 255, 0};
    SDL_Color ColorText = {0, 0, 0, 0};
    SDL_Event event = {0};
    FMOD_SOUND *flipPage = NULL;
    int continued = 1, pageNumber = 1, clickRight = 0, clickLeft = 0, clickQuit = 0;


    FMOD_System_CreateSound(system, "sounds/page.wav", FMOD_CREATESAMPLE, 0, &flipPage);

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

        switch(pageNumber)
        {
            case 1:
                page = IMG_Load("images/page1.png");
                break;

            case 2:
                page = IMG_Load("images/page2.png");
                break;

            case 3:
                page = IMG_Load("images/page3.png");
                break;

            case 4:
                page = IMG_Load("images/page4.png");
                break;

            default:
                break;
        }
        positionPage.x = (window->w / 2) - (page->w / 2);
        positionPage.y = 41;
        SDL_BlitSurface(page, NULL, window, &positionPage);
        SDL_FreeSurface(page);

        switch(pageNumber)
        {
            case 1:
                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_BOLD);
                text = TTF_RenderText_Blended(fontTextNormal, "Votre but est de trouver la combinaison secrète en", ColorText);
                positionText.x = 11;
                positionText.y = 89;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_BOLD);
                text = TTF_RenderText_Blended(fontTextNormal, "10 coups maximum.", ColorText);
                positionText.x = 11;
                positionText.y = 108;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Vous disposez de 8 couleurs :", ColorText);
                positionText.x = 11;
                positionText.y = 153;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                image = IMG_Load("images/colors.jpg");
                positionImage.x = (window->w / 2) - (image->w / 2);
                positionImage.y = 181;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Elles peuvent être présentes à plusieurs reprises dans la", ColorText);
                positionText.x = 11;
                positionText.y = 229;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "combinaison secrète.", ColorText);
                positionText.x = 11;
                positionText.y = 248;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);
                break;

            case 2:
                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Un clic gauche permet de sélectionner une couleur :", ColorText);
                positionText.x = 11;
                positionText.y = 64;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                image = IMG_Load("images/color_selected.jpg");
                positionImage.x = (window->w / 2) - (image->w / 2);
                positionImage.y = 90;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Un second clic gauche permet de la positionner sur un", ColorText);
                positionText.x = 11;
                positionText.y = 140;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "emplacement de votre combinaison :", ColorText);
                positionText.x = 11;
                positionText.y = 159;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                image = IMG_Load("images/color_position.png");
                positionImage.x = (window->w / 2) - (image->w / 2);
                positionImage.y = 187;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Un clic droit sur une couleur de votre combinaison permet", ColorText);
                positionText.x = 11;
                positionText.y = 235;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "de la retirer de son emplacement.", ColorText);
                positionText.x = 11;
                positionText.y = 254;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Vous pouvez également annuler toute votre combinaison", ColorText);
                positionText.x = 11;
                positionText.y = 292;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "en cliquant sur ", ColorText);
                positionText.x = 11;
                positionText.y = 311;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/cancel_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 311;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Une fois votre combinaison terminée, cliquez sur ", ColorText);
                positionText.x = 11;
                positionText.y = 349;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/validate_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 349;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "pour la valider.", ColorText);
                positionText.x = 11;
                positionText.y = 368;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);
                break;

            case 3:
                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Pour chaque couleur proposée présente dans la", ColorText);
                positionText.x = 11;
                positionText.y = 95;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "combinaison secrète mais ", ColorText);
                positionText.x = 11;
                positionText.y = 114;
                SDL_BlitSurface(text, NULL, window, &positionText);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
                positionText.x = positionText.x + text->w;
                positionText.y = 114;
                SDL_FreeSurface(text);
                text = TTF_RenderText_Blended(fontTextNormal, "mal positionnée", ColorText);
                SDL_BlitSurface(text, NULL, window, &positionText);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                positionText.x = positionText.x + text->w;
                positionText.y = 114;
                SDL_FreeSurface(text);
                text = TTF_RenderText_Blended(fontTextNormal, ", un ", ColorText);
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/white.gif");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 119;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "s'affiche à gauche de votre proposition.", ColorText);
                positionText.x = 11;
                positionText.y = 133;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                image = IMG_Load("images/rules_white.png");
                positionImage.x = (window->w / 2) - (image->w / 2);
                positionImage.y = 165;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Pour chaque couleur proposée présente dans la", ColorText);
                positionText.x = 11;
                positionText.y = 228;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "combinaison secrète et ", ColorText);
                positionText.x = 11;
                positionText.y = 247;
                SDL_BlitSurface(text, NULL, window, &positionText);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
                positionText.x = positionText.x + text->w;
                positionText.y = 247;
                SDL_FreeSurface(text);
                text = TTF_RenderText_Blended(fontTextNormal, "bien positionnée", ColorText);
                SDL_BlitSurface(text, NULL, window, &positionText);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                positionText.x = positionText.x + text->w;
                positionText.y = 247;
                SDL_FreeSurface(text);
                text = TTF_RenderText_Blended(fontTextNormal, ", un ", ColorText);
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/black.gif");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 251;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "s'affiche à gauche de votre proposition.", ColorText);
                positionText.x = 11;
                positionText.y = 266;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);

                image = IMG_Load("images/rules_black.png");
                positionImage.x = (window->w / 2) - (image->w / 2);
                positionImage.y = 298;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(image);
                break;

            case 4:
                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Vous pouvez annuler une partie en cliquant sur ", ColorText);
                positionText.x = 11;
                positionText.y = 100;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/exit_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 99;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Vous pouvez désactiver le son en cliquant sur ", ColorText);
                positionText.x = 11;
                positionText.y = 157;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/sound_off_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 157;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "ou le réactiver en cliquant sur ", ColorText);
                positionText.x = 11;
                positionText.y = 174;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/sound_on_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 174;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextNormal, TTF_STYLE_NORMAL);
                text = TTF_RenderText_Blended(fontTextNormal, "Vous pouvez relire ces instructions en cliquant sur ", ColorText);
                positionText.x = 11;
                positionText.y = 223;
                SDL_BlitSurface(text, NULL, window, &positionText);

                image = IMG_Load("images/rulesbook_rules.png");
                positionImage.x = positionText.x + text->w;
                positionImage.y = 223;
                SDL_BlitSurface(image, NULL, window, &positionImage);
                SDL_FreeSurface(text);
                SDL_FreeSurface(image);

                TTF_SetFontStyle(fontTextLarge, TTF_STYLE_NORMAL | TTF_STYLE_ITALIC);
                text = TTF_RenderText_Blended(fontTextLarge, "Bonne réflexion !", ColorText);
                positionText.x = (window->w / 2) - (text->w / 2);
                positionText.y = 289;
                SDL_BlitSurface(text, NULL, window, &positionText);
                SDL_FreeSurface(text);
                break;

            default:
                break;
        }

        if(clickQuit == 0)
        {
            quit = IMG_Load("images/return.png");
        }
        else
        {
            quit = IMG_Load("images/return1.png");
        }
        positionQuit.x = (window->w / 2) - (quit->w / 2);
        positionQuit.y = 396;
        SDL_BlitSurface(quit, NULL, window, &positionQuit);

        if(pageNumber == 1 || pageNumber == 2 || pageNumber == 3)
        {
            if(clickRight == 0)
            {
                right = IMG_Load("images/front.png");
            }
            else
            {
                right = IMG_Load("images/front1.png");
            }
            positionRight.x = (window->w - 17) - right->w;
            positionRight.y = 396;
            SDL_BlitSurface(right, NULL, window, &positionRight);
        }

        if(pageNumber == 2 || pageNumber == 3 || pageNumber == 4)
        {
            if(clickLeft == 0)
            {
                left = IMG_Load("images/back.png");
            }
            else
            {
                left = IMG_Load("images/back1.png");
            }
            positionLeft.x = 17;
            positionLeft.y = 396;
            SDL_BlitSurface(left, NULL, window, &positionLeft);
        }

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
                if((pageNumber == 1 || pageNumber == 2 || pageNumber == 3) && (event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionRight.x && event.button.x <= (positionRight.x + right->w)) && (event.button.y >= positionRight.y && event.button.y <= (positionRight.y + right->h))))
                {
                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, flipPage, 0, NULL);
                    }
                    clickRight = 1;
                }
                else if((pageNumber == 2 || pageNumber == 3 || pageNumber == 4) && (event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionLeft.x && event.button.x <= (positionLeft.x + left->w)) && (event.button.y >= positionLeft.y && event.button.y <= (positionLeft.y + left->h))))
                {
                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, flipPage, 0, NULL);
                    }
                    clickLeft = 1;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionQuit.x && event.button.x <= (positionQuit.x + quit->w)) && (event.button.y >= positionQuit.y && event.button.y <= (positionQuit.y + quit->h)))
                {
                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                    clickQuit = 1;
                }
                SDL_FreeSurface(right);
                SDL_FreeSurface(left);
                SDL_FreeSurface(quit);
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT && clickRight == 1)
                {
                    clickRight = 0;
                    pageNumber++;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickLeft == 1)
                {
                    clickLeft = 0;
                    pageNumber--;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickQuit == 1)
                {
                    clickQuit = 0;
                    continued = 0;
                }
                break;

            default:
                break;
        }
    }

    FMOD_Sound_Release(flipPage);

    if(referer == 1)
    {
        getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }
}
