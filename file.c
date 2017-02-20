#include <stdio.h>
#include <stdlib.h>
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
        fscanf(scoreFile, "%s", player[i].level);
        fscanf(scoreFile, "%d", &player[i].elapseTime);
        fscanf(scoreFile, "%ld", &timestamp);
        dateOfWin = localtime(&timestamp);
        strftime(player[i].currentDate, 25, "Le %d/%m/%Y à %H:%M", dateOfWin);
    }

    fclose(scoreFile);
    return number;
}
