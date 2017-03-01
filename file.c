#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "constants.h"


int getListWinners(Winner *player)
{
    FILE *scoreFile = NULL;
    int line = 0, number = 0, i = 0;
    char stock[100] = {0};
    time_t timestamp = 0;
    struct tm *dateOfWin = NULL;


    scoreFile = fopen("scores.mm", "r");

    while(fgets(stock, 100, scoreFile) != NULL)
    {
        line++;
    }

    number = line / 4;

    if(number > 3)
    {
        number = 3;
    }

    fseek(scoreFile, SEEK_SET, 0);

    for(i = 0; i < number; i++)
    {
        fscanf(scoreFile, "%s", player[i].name);
        fscanf(scoreFile, "%d", &player[i].level);
        fscanf(scoreFile, "%d", &player[i].elapseTime);
        fscanf(scoreFile, "%ld", &timestamp);
        dateOfWin = localtime(&timestamp);
        strftime(player[i].currentDate, 25, "Le %d/%m/%Y à %H:%M", dateOfWin);
    }

    fclose(scoreFile);
    return number;
}


int isBestScore(int shot, int elapsedTime)
{
    FILE *scoreFile = NULL;
    int i = 0, line = 0, number = 0, bestScore = 0;
    char stock[100] = {0};
    Winner player[5] = {{{0}}};


    scoreFile = fopen("scores.mm", "r");

    while(fgets(stock, 100, scoreFile) != NULL)
    {
        line++;
    }

    number = line / 4;

    if(number > 3)
    {
        number = 3;
    }

    fseek(scoreFile, SEEK_SET, 0);

    if(number > 0 && number == 3)
    {
        for(i = 0; i < number; i++)
        {
            fscanf(scoreFile, "%s", player[i].name);
            fscanf(scoreFile, "%d", &player[i].level);
            fscanf(scoreFile, "%d", &player[i].elapseTime);
            fscanf(scoreFile, "%s", player[i].currentDate);
        }

        if(shot < player[number - 1].level)
        {
                bestScore = 1;
        }
        else if(shot == player[number - 1].level)
        {
            if(elapsedTime < (player[number - 1].elapseTime))
            {
                bestScore = 1;
            }
        }
        else
        {
            bestScore = 0;
        }
    }
    else
    {
        bestScore = 1;
    }

    fclose(scoreFile);

    return bestScore;
}


void setBestScore(int shot, int elapsedTime, int actualDate, char *playerName)
{
    FILE *scoreFile = NULL;
    int i = 0, j = 0, line = 0, number = 0, currentLevel = 0;
    char stock[100] = {0}, newPlayerName[10] = {0};
    Winner player[5] = {{{0}}}, newPlayer[5] = {{{0}}};

    if(strcmp("_    _    _    _    _    _    _    _", playerName) == 0)
    {
        sprintf(newPlayerName, "ANONYME");
    }
    else
    {
        j = 0;
        for(i = 0; i <= 35; i++)
        {
            if(playerName[i] != ' ' && playerName[i] != '_')
            {
                newPlayerName[j] = playerName[i];
                j++;
            }
        }
    }

    scoreFile = fopen("scores.mm", "r");

    while(fgets(stock, 100, scoreFile) != NULL)
    {
        line++;
    }

    number = line / 4;

    if(number > 3)
    {
        number = 3;
    }

    fseek(scoreFile, SEEK_SET, 0);

    for(i = 0; i < number; i++)
    {
        fscanf(scoreFile, "%s", player[i].name);
        fscanf(scoreFile, "%d", &player[i].level);
        fscanf(scoreFile, "%d", &player[i].elapseTime);
        fscanf(scoreFile, "%s", player[i].currentDate);
    }

    currentLevel = number;

    for(i = number - 1; i >= 0; i--)
    {
        if(shot < player[i].level)
        {
            currentLevel--;
        }
    }

    for(i = number - 1; i >= 0; i--)
    {
        if(shot == player[i].level && elapsedTime < player[i].elapseTime)
        {
            currentLevel--;
        }
    }

    if(number == 0)
    {
        sprintf(newPlayer[number].name, "%s", newPlayerName);
        newPlayer[number].level = shot;
        newPlayer[number].elapseTime = elapsedTime;
        sprintf(newPlayer[number].currentDate, "%d", actualDate);
        number++;
    }
    else
    {
        sprintf(newPlayer[currentLevel].name, "%s", newPlayerName);
        newPlayer[currentLevel].level = shot;
        newPlayer[currentLevel].elapseTime = elapsedTime;
        sprintf(newPlayer[currentLevel].currentDate, "%d", actualDate);
        number++;

        for(i = 0; i < currentLevel; i++)
        {
            sprintf(newPlayer[i].name, "%s", player[i].name);
            newPlayer[i].level = player[i].level;
            newPlayer[i].elapseTime = player[i].elapseTime;
            sprintf(newPlayer[i].currentDate, "%s", player[i].currentDate);
        }

        for(i = currentLevel; i < number; i++)
        {
            sprintf(newPlayer[i + 1].name, "%s", player[i].name);
            newPlayer[i + 1].level = player[i].level;
            newPlayer[i + 1].elapseTime = player[i].elapseTime;
            sprintf(newPlayer[i + 1].currentDate, "%s", player[i].currentDate);
        }
    }

    fclose(scoreFile);

    scoreFile = fopen("scores.mm", "w");

    if(number > 3)
    {
        number = 3;
    }

    for(i = 0; i < number; i++)
    {
        fprintf(scoreFile, "%s\n", newPlayer[i].name);
        fprintf(scoreFile, "%d\n", newPlayer[i].level);
        fprintf(scoreFile, "%d\n", newPlayer[i].elapseTime);
        fprintf(scoreFile, "%s\n", newPlayer[i].currentDate);
    }

    fclose(scoreFile);
}
