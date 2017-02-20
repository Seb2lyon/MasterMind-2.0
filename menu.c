#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fmodex/fmod.h"
#include "constants.h"
#include "about.h"
#include "rules.h"
#include "scores.h"
#include "game.h"


void getMenuPage(SDL_Surface *window, int sound, TTF_Font *fontTitle, TTF_Font *fontTextLarge, TTF_Font *fontTextNormal, TTF_Font *fontTextSmall, FMOD_SYSTEM *system, FMOD_SOUND *button)
{
    SDL_Surface *background = NULL, *title = NULL, *game = NULL, *scores = NULL, *rules = NULL, *quit = NULL, *about = NULL, *sound_on = NULL;
    SDL_Rect positionBackground = {0}, positionTitle = {0}, positionGame = {0}, positionScores = {0}, positionRules = {0}, positionQuit = {0}, positionAbout = {0}, positionSound_on = {0};
    SDL_Color colorTitle = {255, 255, 255, 0};
    SDL_Event event = {0};
    int continued = 1, clickGame = 0, clickScores = 0, clickRules = 0, clickQuit = 0, clickAbout = 0, referer = 1, goAbout = 0, goRules = 0, goScores = 0, goGame = 0;


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

    game = IMG_Load("images/play.png");
    positionGame.x = (window->w / 2) - (game->w / 2);
    positionGame.y = 131;
    SDL_BlitSurface(game, NULL, window, &positionGame);

    scores = IMG_Load("images/scores.png");
    positionScores.x = (window->w / 2) - (scores->w / 2);
    positionScores.y = 196;
    SDL_BlitSurface(scores, NULL, window, &positionScores);

    rules = IMG_Load("images/rules.png");
    positionRules.x = (window->w / 2) - (rules->w / 2);
    positionRules.y = 260;
    SDL_BlitSurface(rules, NULL, window, &positionRules);

    quit = IMG_Load("images/quit.png");
    positionQuit.x = (window->w / 2) - (quit->w / 2);
    positionQuit.y = 323;
    SDL_BlitSurface(quit, NULL, window, &positionQuit);

    about = IMG_Load("images/about.png");
    positionAbout.x = 17;
    positionAbout.y = 411;
    SDL_BlitSurface(about, NULL, window, &positionAbout);

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
                if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionGame.x && event.button.x <= (positionGame.x + game->w)) && (event.button.y >= positionGame.y && event.button.y <= (positionGame.y + game->h)))
                {
                    SDL_FreeSurface(game);
                    game = IMG_Load("images/play1.png");
                    SDL_BlitSurface(game, NULL, window, &positionGame);
                    SDL_FreeSurface(game);
                    SDL_Flip(window);
                    clickGame = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionScores.x && event.button.x <= (positionScores.x + scores->w)) && (event.button.y >= positionScores.y && event.button.y <= (positionScores.y + scores->h)))
                {
                    SDL_FreeSurface(scores);
                    scores = IMG_Load("images/scores1.png");
                    SDL_BlitSurface(scores, NULL, window, &positionScores);
                    SDL_FreeSurface(scores);
                    SDL_Flip(window);
                    clickScores = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionRules.x && event.button.x <= (positionRules.x + rules->w)) && (event.button.y >= positionRules.y && event.button.y <= (positionRules.y + rules->h)))
                {
                    SDL_FreeSurface(rules);
                    rules = IMG_Load("images/rules1.png");
                    SDL_BlitSurface(rules, NULL, window, &positionRules);
                    SDL_FreeSurface(rules);
                    SDL_Flip(window);
                    clickRules = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionQuit.x && event.button.x <= (positionQuit.x + quit->w)) && (event.button.y >= positionQuit.y && event.button.y <= (positionQuit.y + quit->h)))
                {
                    SDL_FreeSurface(quit);
                    quit = IMG_Load("images/quit1.png");
                    SDL_BlitSurface(quit, NULL, window, &positionQuit);
                    SDL_FreeSurface(quit);
                    SDL_Flip(window);
                    clickQuit = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionAbout.x && event.button.x <= (positionAbout.x + about->w)) && (event.button.y >= positionAbout.y && event.button.y <= (positionAbout.y + about->h)))
                {
                    SDL_FreeSurface(about);
                    about = IMG_Load("images/about1.png");
                    SDL_BlitSurface(about, NULL, window, &positionAbout);
                    SDL_FreeSurface(about);
                    SDL_Flip(window);
                    clickAbout = 1;

                    if(sound)
                    {
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }
                }
                else if(event.button.button == SDL_BUTTON_LEFT && (event.button.x >= positionSound_on.x && event.button.x <= (positionSound_on.x + sound_on->w)) && (event.button.y >= positionSound_on.y && event.button.y <= (positionSound_on.y + sound_on->h)))
                {
                    SDL_FreeSurface(sound_on);

                    if(sound)
                    {
                        sound_on = IMG_Load("images/sound_off.png");
                        sound = 0;
                    }
                    else
                    {
                        sound_on = IMG_Load("images/sound_on.png");
                        sound = 1;
                        FMOD_System_PlaySound(system, 1, button, 0, NULL);
                    }

                    SDL_BlitSurface(sound_on, NULL, window, &positionSound_on);
                    SDL_Flip(window);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT && clickGame == 1)
                {
                    game = IMG_Load("images/play.png");
                    SDL_BlitSurface(game, NULL, window, &positionGame);
                    SDL_Flip(window);
                    clickGame = 0;

                    goGame = 1;

                    continued = 0;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickScores == 1)
                {
                    scores = IMG_Load("images/scores.png");
                    SDL_BlitSurface(scores, NULL, window, &positionScores);
                    SDL_Flip(window);
                    clickScores = 0;

                    goScores = 1;

                    continued = 0;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickRules == 1)
                {
                    rules = IMG_Load("images/rules.png");
                    SDL_BlitSurface(rules, NULL, window, &positionRules);
                    SDL_Flip(window);
                    clickRules = 0;

                    goRules = 1;

                    continued = 0;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickQuit == 1)
                {
                    quit = IMG_Load("images/quit.png");
                    SDL_BlitSurface(quit, NULL, window, &positionQuit);
                    SDL_Flip(window);
                    clickQuit = 0;

                    continued = 0;
                }
                else if(event.button.button == SDL_BUTTON_LEFT && clickAbout == 1)
                {
                    about = IMG_Load("images/about.png");
                    SDL_BlitSurface(about, NULL, window, &positionAbout);
                    SDL_Flip(window);
                    clickAbout = 0;

                    goAbout = 1;

                    continued = 0;
                }
                break;

            default:
                break;
        }
    }

    SDL_FreeSurface(game);
    SDL_FreeSurface(scores);
    SDL_FreeSurface(rules);
    SDL_FreeSurface(quit);
    SDL_FreeSurface(about);
    SDL_FreeSurface(sound_on);

    if(goAbout)
    {
        getAboutPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button, referer);
    }

    if(goRules)
    {
        getRulesPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button, referer);
    }

    if(goScores)
    {
        getScoresPage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }

    if(goGame)
    {
        getGamePage(window, sound, fontTitle, fontTextLarge, fontTextNormal, fontTextSmall, system, button);
    }
}
