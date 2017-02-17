#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"


int getListWinners(Winner *player)
{
    FILE *scoreFile = NULL;
    int line = 0, number = 0, i = 0;
    char stock[100] = {0};

    scoreFile = fopen("scores.mm", "r");

    while(fgets(stock, 100, scoreFile) != NULL)
    {
        line++;
    }

    number = line / 4;

    fseek(scoreFile, SEEK_SET, 0);

    for(i = 0; i < number; i++)
    {
        fscanf(scoreFile, "%s", player[i].name);
        fscanf(scoreFile, "%s", player[i].level);
        fscanf(scoreFile, "%d", &player[i].elapseTime);
        fscanf(scoreFile, "%s", player[i].currentDate);
    }

    // Formater la phrase de date et heure

    fclose(scoreFile);
    return number;
}
