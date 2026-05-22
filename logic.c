#include "headers.h"

#define PLATFORM_STEP  1    /* platform speed */
extern char* buff;
extern short current_key;

/* initialize ball */
ball Ball;

/* initialize platform */
platform Platform;

int total_bricks;
brick *Bricks = NULL;

void compute(void)
{
    /* UPDATE BALL */
    Ball.x += Ball.Vx;
    Ball.y += Ball.Vy;

    /* UPDATE PLATFORM */
    if (current_key != 0) {
        switch(current_key) {
            case 68:    /* left arrow */
                Platform.x -= PLATFORM_STEP;
                Platform.xE -= PLATFORM_STEP;
                break;
            case 67:    /* right arrow */
                Platform.x += PLATFORM_STEP;
                Platform.xE += PLATFORM_STEP;
                break;
        }
        current_key = 0;
    }
}

void to_buff(void)
{
    /* RENDER BALL */
    buff[((int)Ball.y * SIZE_X) + (int)Ball.x] = BALL;

    /* RENDER PLATFORM */
    for (int i = Platform.x; i <= Platform.xE; ++i)
        buff[((int)Platform.y * SIZE_X) + i] = PLATFORM;

    /* RENDER BRICKS */
    for (int i = 0; i < total_bricks; ++i) {
        if (Bricks[i].y == -1) continue;

        for (int j = Bricks[i].init_x; j < Bricks[i].fin_x; ++j)
            buff[((int)Bricks[i].y * SIZE_X) + j] = BRICK;
    }
}

