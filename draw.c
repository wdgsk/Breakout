#include "headers.h"

#define clr_scr()               printf("\e[H\e[2J\e[3J")

#define clr_buff(buff, maxRes)  for (int i = 0; i < maxRes; ++i) \
                                    buff[i] = EMPTY_C;

#define init_buff(type, row, col) (type *) \
        calloc(SIZE_Y * SIZE_X, sizeof(type))

char* buff = NULL;

unsigned int MAX_RES = 0;
unsigned int SIZE_X = 0;
unsigned int SIZE_Y = 0;

int init_draw(void)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    SIZE_Y = w.ws_row;
    SIZE_X = w.ws_col;

    MAX_RES = SIZE_Y * SIZE_X;

    if ((buff = init_buff(
        char,
        SIZE_Y,
        SIZE_X)) == NULL)
        return 1;
    else
        return 0;
}

void draw(void)
{
    clr_scr();
    //buff[(10 * SIZE_X) + 41] = BALL;

    for (int ind = 0; ind < MAX_RES; ++ind) {
        if ((ind % SIZE_X) == 0)
            putchar('\n');

        if (buff[ind] == 0)
            putchar(EMPTY_C);
        else
            putchar(buff[ind]);
    }

    clr_buff(buff, MAX_RES);
}
