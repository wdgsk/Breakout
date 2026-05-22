#include "headers.h"
#include <math.h>

#define MAX_B_ANGLE 3.141593

extern ball Ball;
extern platform Platform;
extern brick* Bricks;
extern int total_bricks;
extern short touchedGrd;

float relativeIntersect;
float norRelativeIntersect;
float bounceAngle;

int collision(void)
{
    /* WALL COLLISION */
    if (Ball.y >= SIZE_Y-2) {
        Ball.y = SIZE_Y-2;
        Ball.Vy *= -1;
        touchedGrd = 1; /* touched the floor */
        return 0;
    } else if (Ball.y <= 0) {
        Ball.y = 0;
        Ball.Vy *= -1;
    }

    if (Ball.x >= SIZE_X-1) {
        Ball.x = SIZE_X-1;
        Ball.Vx *= -1;
    } else if (Ball.x <= 0) {
        Ball.x = 0;
        Ball.Vx *= -1;
    }

    /* PLATFORM - WALL COLLISION */
    if ((int)Platform.x < 1) {
        Platform.x = 1;
        Platform.xE = 0 + Platform.xE + 1;
    } else if ((int)Platform.xE > SIZE_X - 1) {
        Platform.xE = SIZE_X - 1;
        Platform.x = SIZE_X - (SIZE_X - Platform.x) - 1;
    }

    /* PLATFORM COLLISION */
    if ((int)Ball.y == Platform.y &&
        (int)Ball.x >= Platform.x &&
        (int)Ball.x <= Platform.xE) {
        Ball.y = Platform.y - 1;

        relativeIntersect = ((Platform.x + Platform.xE) / 2.0) - Ball.x;
        norRelativeIntersect = (relativeIntersect / ((Platform.x + Platform.xE) / 2.0)) * -1;
        bounceAngle = norRelativeIntersect * MAX_B_ANGLE;
        Ball.Vx = Ball.speed * sin(bounceAngle);
        Ball.Vy = Ball.speed * -cos(bounceAngle);
    }

    /* BRICKS COLLISION */
    for (int i = 0; i < total_bricks; ++i) {
        if (Bricks[i].y == -1) continue;

        if ((int)Ball.y == Bricks[i].y + 1 &&
            (int)Ball.x >= Bricks[i].init_x &&
            (int)Ball.x <= Bricks[i].fin_x) {

            Ball.y = Bricks[i].y + 1;
            Ball.Vy *= -1;

            Bricks[i].y = -1;
            return 1;
        }
    }
    return 0;
}
