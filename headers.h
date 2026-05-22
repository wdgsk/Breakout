#ifndef HEADERS
#define HEADERS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <termios.h>

#define EMPTY_C     ' '
#define PLATFORM    '-'
#define BRICK       '#'
#define BALL        'o'

extern unsigned int MAX_RES;
extern unsigned int SIZE_X;
extern unsigned int SIZE_Y;

int init_draw(void);
void draw(void);
void *input (void *arg);
void enableRawMode(void);
void restoreMode(void);
int collision(void);

typedef struct {
    float x;
    float y;

    float Vx;
    float Vy;

    float speed;
} ball;

typedef struct {
    float x;
    float y;

    float xE;
} platform;

typedef struct {
    int init_x; /* beginning of a brick */
    int fin_x;  /* end of a brick */

    int y;
} brick;

#endif
