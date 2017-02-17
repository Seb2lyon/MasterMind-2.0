#ifndef CONSTANTS
#define CONSTANTS

#define WINDOW_W 450
#define WINDOW_H 450
#define TITLE "MASTERMIND 2.0"

typedef struct Winner Winner;

struct Winner
{
    char name[10];
    char level[5];
    int elapseTime;
    char currentDate[25];
};

#endif // CONSTANTS
