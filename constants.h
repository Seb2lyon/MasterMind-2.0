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

#define PAWN(objective)\
\
case 1:\
    objective = IMG_Load("images/color_1.gif");\
    break;\
\
case 2:\
    objective = IMG_Load("images/color_2.gif");\
    break;\
\
case 3:\
    objective = IMG_Load("images/color_3.gif");\
    break;\
\
case 4:\
    objective = IMG_Load("images/color_4.gif");\
    break;\
\
case 5:\
    objective = IMG_Load("images/color_5.gif");\
    break;\
\
case 6:\
    objective = IMG_Load("images/color_6.gif");\
    break;\
\
case 7:\
    objective = IMG_Load("images/color_7.gif");\
    break;\
\
case 8:\
    objective = IMG_Load("images/color_8.gif");\
    break;\
\
default:\
    break;\


#endif // CONSTANTS
