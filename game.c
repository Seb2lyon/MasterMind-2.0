#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "menu.h"
#include "about.h"
#include "rules.h"


void getGamePage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button)
{
    SDL_Surface *background = NULL, *board = NULL, *secretBoard = NULL, *secretCode = NULL, *about = NULL, *sound_on = NULL, *rulesbook = NULL, *quit = NULL, *cancel = NULL, *validate = NULL, *color = NULL, *choice = NULL, *mouse = NULL, *arrow = NULL, *text = NULL;
    SDL_Rect positionBackground = {0}, positionBoard = {0}, positionSecretBoard = {0}, positionSecretCode = {0}, positionAbout = {0}, positionSound_on = {0}, positionRulesbook = {0}, positionQuit = {0}, positionCancel = {0}, positionValidate = {0}, positionColor = {0}, positionChoice = {0}, positionMouse = {0}, positionArrow = {0}, positionText = {0};
    SDL_Color text1 = {0, 0, 0, 0};
    SDL_Color text2 = {255, 255, 255, 0};
    SDL_Event event = {0};
    TTF_Font *fontTextXLarge = NULL, *fontNumber = NULL;
    FMOD_SOUND *pawn = NULL, *cancelButton = NULL, *validateButton = NULL;
    int continued = 1, i = 0, j = 0, startTime = 0, currentTime = 0, elapsedTime = 0, minutes = 0, seconds = 0, referer = 0, selected = 0, stock = 0, clickPawn = 0, clickAbout = 0, clickRules = 0, clickSound = 0, clickQuit = 0, clickCancel = 0, clickValidate = 0, shot = 1, theEnd = 0, secret[5] = {0}, colorChoice[11][5] = {{0}};
    char showShots[6] = {0}, showTime[10] = {0};


    startTime = SDL_GetTicks();

    FMOD_System_CreateSound(system, "sounds/pawn.wav", FMOD_CREATESAMPLE, 0, &pawn);
    FMOD_System_CreateSound(system, "sounds/reload.wav", FMOD_CREATESAMPLE, 0, &cancelButton);
    FMOD_System_CreateSound(system, "sounds/validate.wav", FMOD_CREATESAMPLE, 0, &validateButton);

    fontTextXLarge = TTF_OpenFont("fonts/letters.ttf", 28);
    fontNumber = TTF_OpenFont("fonts/number.ttf", 25);

    srand(time(NULL));

    for(i = 0; i < 4; i++)
    {
        secret[i] = rand()%(9 - 1) + 1;
    }

    while(continued)
    {
        // Background
        background = SDL_CreateRGBSurface(SDL_HWSURFACE, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
        SDL_FillRect(background, NULL, SDL_MapRGB(window->format, 150, 150, 150));
        positionBackground.x = 0;
        positionBackground.y = 0;
        SDL_BlitSurface(background, NULL, window, &positionBackground);
        SDL_FreeSurface(background);

        // Board
        board = IMG_Load("images/board.png");
        positionBoard.x = (window->w / 2) - (board->w / 2);
        positionBoard.y = 7;
        SDL_BlitSurface(board, NULL, window, &positionBoard);

        // Show the secret code
        if(theEnd)
        {
            positionSecretCode.x = positionBoard.x + 90;
            positionSecretCode.y = positionBoard.y + 14;

            for(i = 0; i < 4; i++)
            {
                switch(secret[i])
                {
                    PAWN(secretCode)
                }
                SDL_BlitSurface(secretCode, NULL, window, &positionSecretCode);
                SDL_FreeSurface(secretCode);
                positionSecretCode.x += 30;
            }
        }
        // Hide the secret code
        else
        {
            secretBoard = IMG_Load("images/hide.png");
            positionSecretBoard.x = positionBoard.x + 63;
            positionSecretBoard.y = positionBoard.y + 15;
            SDL_BlitSurface(secretBoard, NULL, window, &positionSecretBoard);
            SDL_FreeSurface(secretBoard);
        }

        // Arrow
        arrow = IMG_Load("images/arrow.png");
        positionArrow.x = positionBoard.x - arrow->w;
        positionArrow.y = 335 + 30 - (30 * shot);
        SDL_BlitSurface(arrow, NULL, window, &positionArrow);
        SDL_FreeSurface(arrow);

        // Rules
        if(clickRules == 0)
        {
            rulesbook = IMG_Load("images/rulesbook.png");
        }
        else
        {
            rulesbook = IMG_Load("images/rulesbook1.png");
        }
        positionRulesbook.x = (positionBoard.x / 2) - (rulesbook->w / 2);
        positionRulesbook.y = 8;
        SDL_BlitSurface(rulesbook, NULL, window, &positionRulesbook);
        SDL_FreeSurface(rulesbook);

        // Quit
        if(clickQuit == 0)
        {
            quit = IMG_Load("images/exit.png");
        }
        else
        {
            quit = IMG_Load("images/exit1.png");
        }
        positionQuit.x = window->w - positionRulesbook.x - quit->w;
        positionQuit.y = 10;
        SDL_BlitSurface(quit, NULL, window, &positionQuit);
        SDL_FreeSurface(quit);

        // About
        if(clickAbout == 0)
        {
            about = IMG_Load("images/about.png");
        }
        else
        {
            about = IMG_Load("images/about1.png");
        }
        positionAbout.x = 17;
        positionAbout.y = 411;
        SDL_BlitSurface(about, NULL, window, &positionAbout);
        SDL_FreeSurface(about);

        // Sound
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

        // Cancel
        if(clickCancel == 0)
        {
            cancel = IMG_Load("images/cancel.png");
            positionCancel.y = 128;
        }
        else
        {
            cancel = IMG_Load("images/cancel1.png");
            positionCancel.y = 130;
        }
        positionCancel.x = (positionBoard.x / 2) - (cancel->w / 2);
        SDL_BlitSurface(cancel, NULL, window, &positionCancel);
        SDL_FreeSurface(cancel);

        // Validate
        if(clickValidate == 0)
        {
            validate = IMG_Load("images/validate.png");
            positionValidate.y = 228;
        }
        else
        {
            validate = IMG_Load("images/validate1.png");
            positionValidate.y = 230;
        }
        positionValidate.x = (positionBoard.x / 2) - (validate->w / 2);
        SDL_BlitSurface(validate, NULL, window, &positionValidate);
        SDL_FreeSurface(validate);

        // Colors available (selected or not)
        positionColor.y = 383;

        if(selected != 0)
        {
            color = IMG_Load("images/select.png");
            positionColor.x = positionBoard.x - 31 + (31 * selected);
            SDL_BlitSurface(color, NULL, window, &positionColor);
            SDL_FreeSurface(color);

            SDL_ShowCursor(SDL_DISABLE);
            SDL_BlitSurface(mouse, NULL, window, &positionMouse);
        }
        else
        {
            SDL_ShowCursor(SDL_ENABLE);
        }

        positionColor.x = positionBoard.x;

        for(i = 1; i <= 8; i++)
        {
            switch(i)
            {
                PAWN(color)
            }
            SDL_BlitSurface(color, NULL, window, &positionColor);
            SDL_FreeSurface(color);
            positionColor.x += 31;
        }

        // Colors placed on the board
        positionChoice.y = positionBoard.y + 330;

        for(j = 0; j < 10; j++)
        {
            positionChoice.x = positionBoard.x + 90;

            for(i = 0; i < 4; i++)
            {
                switch(colorChoice[j][i])
                {
                    PAWN(choice)
                }

                if(colorChoice[j][i] != 0)
                {
                    SDL_BlitSurface(choice, NULL, window, &positionChoice);
                    SDL_FreeSurface(choice);
                }

                positionChoice.x += 30;
            }

            positionChoice.y -= 30;
        }

        // Number of shots
        TTF_SetFontStyle(fontTextXLarge, TTF_STYLE_NORMAL);
        text = TTF_RenderText_Blended(fontTextXLarge, "Coup", text1);
        positionText.x = positionBoard.x + board->w + 15;
        positionText.y = 120;
        SDL_BlitSurface(text, NULL, window, &positionText);
        SDL_FreeSurface(text);

        if(shot < 10)
        {
            sprintf(showShots, "0%d/10", shot);
        }
        else
        {
            sprintf(showShots, "%d/10", shot);
        }

        TTF_SetFontStyle(fontNumber, TTF_STYLE_NORMAL);
        text = TTF_RenderText_Blended(fontNumber, showShots, text2);
        positionText.x = positionBoard.x + board->w + 15;
        positionText.y = 150;
        SDL_BlitSurface(text, NULL, window, &positionText);
        SDL_FreeSurface(text);

        // Elapsed time
        TTF_SetFontStyle(fontTextXLarge, TTF_STYLE_NORMAL);
        text = TTF_RenderText_Blended(fontTextXLarge, "Temps", text1);
        positionText.x = positionBoard.x + board->w + 15;
        positionText.y = 220;
        SDL_BlitSurface(text, NULL, window, &positionText);
        SDL_FreeSurface(text);

        currentTime = SDL_GetTicks();
        elapsedTime = currentTime - startTime;
        elapsedTime /= 1000;
        minutes = elapsedTime / 60;
        seconds = elapsedTime % 60;

        if(minutes < 10 && seconds < 10)
        {
            sprintf(showTime, "0%d:0%d", minutes, seconds);
        }
        else if(minutes < 10 && seconds >= 10)
        {
            sprintf(showTime, "0%d:%d", minutes, seconds);
        }
        else if(minutes >= 10 && seconds < 10)
        {
            sprintf(showTime, "%d:0%d", minutes, seconds);
        }
        else if(minutes >= 10 && seconds >= 10)
        {
            sprintf(showTime, "%d:%d", minutes, seconds);
        }

        TTF_SetFontStyle(fontNumber, TTF_STYLE_NORMAL);
        text = TTF_RenderText_Blended(fontNumber, showTime, text2);
        positionText.x = positionBoard.x + board->w + 15;
        positionText.y = 250;
        SDL_BlitSurface(text, NULL, window, &positionText);
        SDL_FreeSurface(text);

        SDL_FreeSurface(board);

        SDL_Flip(window);


        // Events
        SDL_PollEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continued = 0;
                SDL_ShowCursor(SDL_ENABLE);
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continued = 0;
                    SDL_ShowCursor(SDL_ENABLE);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // Click to select color
                    if(clickPawn == 0 && event.button.y >= 383 && event.button.y < 383 + 31 && event.button.x >= positionBoard.x && event.button.x < positionBoard.x + (31 * 8))
                    {
                        // Select color
                        for(i = 1; i <= 8; i++)
                        {
                            if(event.button.x >= (positionBoard.x - 31 + (31 * i)) && event.button.x < (positionBoard.x  - 31 + (31 * i) + 31))
                            {
                                if(sound)
                                {
                                    FMOD_System_PlaySound(system, 1, pawn, 0, NULL);
                                }
                                selected = i;
                                clickPawn = 1;
                                SDL_FreeSurface(mouse);
                            }
                        }

                        // Mouse turn into color
                        switch(selected)
                        {
                            PAWN(mouse)
                        }
                        positionMouse.x = event.button.x - (mouse->w / 2);
                        positionMouse.y = event.button.y - (mouse->h / 2);
                    }

                    // Click to place pawn
                    else if(selected != 0 && clickPawn == 0)
                    {
                        if(event.button.y >= ((positionBoard.y + 330) + 30 - (shot * 30)) && event.button.y <= ((positionBoard.y + 330) + 30 - (shot * 30) + 30) && event.button.x >= (positionBoard.x + 90) && event.button.x <= ((positionBoard.x + 90) + (30 * 4)))
                        {
                            if(sound)
                            {
                                FMOD_System_PlaySound(system, 1, pawn, 0, NULL);
                            }
                            colorChoice[shot - 1][(event.button.x - (positionBoard.x + 90)) / 30] = selected;
                            clickPawn = 1;
                        }
                    }

                    // Click "Cancel" button
                    else if(clickCancel == 0 && event.button.x >= positionCancel.x && event.button.x <= positionCancel.x + 40 && event.button.y >= positionCancel.y && event.button.y <= positionCancel.y + 40)
                    {
                        for(i = 0; i < 4; i++)
                        {
                            colorChoice[shot - 1][i] = 0;
                        }

                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, cancelButton, 0, NULL);
                        }
                        clickCancel = 1;
                    }

                    // Click "Validate" button
                    else if(clickValidate == 0 && event.button.x >= positionValidate.x && event.button.x <= positionValidate.x + 40 && event.button.y >= positionValidate.y && event.button.y <= positionValidate.y + 40)
                    {

                        // ALL THE CHECKINGS TO DO

                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, validateButton, 0, NULL);
                        }
                        clickValidate = 1;
                    }

                    // Click to go to "About" page
                    else if(clickAbout == 0 && event.button.x >= positionAbout.x && event.button.x <= positionAbout.x + 30 && event.button.y >= positionAbout.y && event.button.y <= positionAbout.y + 30)
                    {
                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }
                        clickAbout = 1;
                    }

                    // Click to go to "Rules" page
                    else if(clickRules == 0 && event.button.x >= positionRulesbook.x && event.button.x <= positionRulesbook.x + 40 && event.button.y >= positionRulesbook.y && event.button.y <= positionRulesbook.y + 40)
                    {
                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }
                        clickRules = 1;
                    }

                    // Click to go to "Menu" page
                    else if(clickQuit == 0 && event.button.x >= positionQuit.x && event.button.x <= positionQuit.x + 40 && event.button.y >= positionQuit.y && event.button.y <= positionQuit.y + 40)
                    {
                        if(sound)
                        {
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }
                        clickQuit = 1;
                    }

                    // Click to turn on/off the sound
                    else if(event.button.x >= positionSound_on.x && clickSound == 0 && event.button.x <= positionSound_on.x + 40 && event.button.y >= positionSound_on.y && event.button.y <= positionSound_on.y + 40)
                    {
                        if(sound)
                        {
                            sound = 0;
                        }
                        else
                        {
                            sound = 1;
                            FMOD_System_PlaySound(system, 1, button, 0, NULL);
                        }
                        clickSound = 1;
                    }
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    // Cancel active pawn
                    if(clickPawn == 0)
                    {
                        if(event.button.y >= ((positionBoard.y + 330) + 30 - (shot * 30)) && event.button.y <= ((positionBoard.y + 330) + 30 - (shot * 30) + 30) && event.button.x >= (positionBoard.x + 90) && event.button.x <= ((positionBoard.x + 90) + (30 * 4)))
                        {
                            if(sound)
                            {
                                FMOD_System_PlaySound(system, 1, pawn, 0, NULL);
                            }
                            colorChoice[shot - 1][(event.button.x - (positionBoard.x + 90)) / 30] = 0;
                        }
                        else
                        {
                            selected = 0;
                        }
                        clickPawn = 1;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(clickAbout == 1)
                {
                    about = IMG_Load("images/about.png");
                    SDL_BlitSurface(about, NULL, window, &positionAbout);
                    SDL_FreeSurface(about);
                    clickAbout = 0;
                    selected = 0;
                    stock = 0;
                    SDL_ShowCursor(SDL_ENABLE);
                    getAboutPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button, referer);
                }

                if(clickRules == 1)
                {
                    clickRules = 0;
                    selected = 0;
                    stock = 0;
                    SDL_ShowCursor(SDL_ENABLE);
                    getRulesPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button, referer);
                }

                if(clickPawn == 1)
                {
                    clickPawn = 0;
                }

                if(clickSound == 1)
                {
                    clickSound = 0;
                }

                if(clickQuit == 1)
                {
                    clickQuit = 0;
                    SDL_ShowCursor(SDL_ENABLE);
                    continued = 0;
                }

                if(clickCancel == 1)
                {
                    clickCancel = 0;
                    selected = 0;
                    stock = 0;
                }

                if(clickValidate == 1)
                {
                    clickValidate = 0;
                    selected = 0;
                    stock = 0;
                }
                break;

            case SDL_MOUSEMOTION:
                // Manage the cursor picture when it goes over a button
                if(selected != 0)
                {
                    if((event.motion.x >= positionAbout.x && event.motion.x <= positionAbout.x + 30 && event.motion.y >= positionAbout.y && event.motion.y <= positionAbout.y + 30) || (event.motion.x >= positionRulesbook.x && event.motion.x <= positionRulesbook.x + 40 && event.motion.y >= positionRulesbook.y && event.motion.y <= positionRulesbook.y + 40) || (event.motion.x >= positionQuit.x && event.motion.x <= positionQuit.x + 40 && event.motion.y >= positionQuit.y && event.motion.y <= positionQuit.y + 40) || (event.motion.x >= positionSound_on.x && event.motion.x <= positionSound_on.x + 40 && event.motion.y >= positionSound_on.y && event.motion.y <= positionSound_on.y + 40) || (event.motion.x >= positionBoard.x && event.motion.x <= positionBoard.x + (31 * 8) && event.motion.y >= positionColor.y && event.motion.y <= positionColor.y + 30) || (event.motion.x >= positionCancel.x && event.motion.x <= positionCancel.x + 40 && event.motion.y >= positionCancel.y && event.motion.y <= positionCancel.y + 40) || (event.motion.x >= positionValidate.x && event.motion.x <= positionValidate.x + 40 && event.motion.y >= positionValidate.y && event.motion.y <= positionValidate.y + 40))
                    {
                        stock = selected;
                        selected = 0;
                    }
                    else
                    {
                        positionMouse.x = event.motion.x - (mouse->w / 2);
                        positionMouse.y = event.motion.y - (mouse->h / 2);
                    }
                }
                else if(stock != 0)
                {
                    if((event.motion.x < positionAbout.x || event.motion.x > positionAbout.x + 30 || event.motion.y < positionAbout.y || event.motion.y > positionAbout.y + 30) && (event.motion.x < positionRulesbook.x || event.motion.x > positionRulesbook.x + 40 || event.motion.y < positionRulesbook.y || event.motion.y > positionRulesbook.y + 40) && (event.motion.x < positionQuit.x || event.motion.x > positionQuit.x + 40 || event.motion.y < positionQuit.y || event.motion.y > positionQuit.y + 40) && (event.motion.x < positionSound_on.x || event.motion.x > positionSound_on.x + 40 || event.motion.y < positionSound_on.y || event.motion.y > positionSound_on.y + 40) && (event.motion.x < positionBoard.x || event.motion.x > positionBoard.x + (31 * 8) || event.motion.y < positionColor.y || event.motion.y > positionColor.y + 30) && (event.motion.x < positionCancel.x || event.motion.x > positionCancel.x + 40 || event.motion.y < positionCancel.y || event.motion.y > positionCancel.y + 40) && (event.motion.x < positionValidate.x || event.motion.x > positionValidate.x + 40 || event.motion.y < positionValidate.y || event.motion.y > positionValidate.y + 40))
                    {
                        selected = stock;
                        stock = 0;
                        switch(selected)
                        {
                            PAWN(mouse)
                        }
                        positionMouse.x = event.motion.x - (mouse->w / 2);
                        positionMouse.y = event.motion.y - (mouse->h / 2);
                    }
                }
                break;

            default:
                break;
        }
    }

    FMOD_Sound_Release(pawn);
    FMOD_Sound_Release(cancelButton);
    FMOD_Sound_Release(validateButton);
    TTF_CloseFont(fontNumber);
    TTF_CloseFont(fontTextXLarge);
    getMenuPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
}
