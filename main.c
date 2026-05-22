#include "headers.h"
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

#define initball(x, y, Vx, Vy, speed)   Ball = (ball){    \
                                                x, \
                                                y, \
                                                Vx,\
                                                Vy,\
                                                speed   \
                                                }

#define initplaform(x, y, endx) Platform = (platform){  \
                                            x,  \
                                            y,  \
                                            endx    \
                                            }

void print_buff(char* buff, char* s, int x, int y)
{
    while (*s != '\0')
        buff[y * SIZE_X + x++] = *(s++);
}

void compute(void);
void to_buff(void);
brick* extract(int* totalbricks, char* fileDir);

extern char* buff;
extern int total_bricks;
extern brick *Bricks;
extern ball Ball;
extern platform Platform;
extern short current_key;

char dirName[] = "levels/"; /* directory name */
short touchedGrd = 0;

#define BALL_SPEED_INC  0.1

#define DEF_X_RES   40
#define DEF_Y_RES   25
int main(int argc, char** argv)
{
    if (init_draw() == 1) {
        fprintf(stderr, "Init draw failed\n");
        return 1;
    }

    /* check default res */
    if (argc == 1) {    /* resolutions doesn't match */
        if (DEF_X_RES != SIZE_X ||
            DEF_Y_RES != SIZE_Y) {
            printf("Error: resize terminal to X=%d\tY=%d\n", DEF_X_RES, DEF_Y_RES);
            printf("Current resolution: X=%d\tY=%d\n", SIZE_X, SIZE_Y);
            printf("Use [--no-res] to bypass the restriction\n");
            return 1;
        }
    } else if (argc == 2) { /* arguments doesn't match */
        if (strcmp("--no-res", argv[1]) || argc > 2) {
            printf("Error: invalid option\n");
            return 1;
        }
    }

    /* Open directory */
    struct dirent *df;
    DIR* dr;
    if ((dr = opendir(dirName)) == NULL) {
        fprintf(stderr, "Can't open: %s\n", dirName);
        return 1;
    }

    enableRawMode();

    pthread_t input_t;
    pthread_create(&input_t, NULL, input, NULL);

    int score, total_score = 0, prev_score;
    char tempdir[100];
    char print_lvl[10];
    char print_score[10];
    strcpy(tempdir, dirName);

    while ((df = readdir(dr)) != NULL) {    /* directory loop */
        if (df->d_type == DT_DIR) continue;
        if (Bricks != NULL) free(Bricks);
        strcat(tempdir, df->d_name);
        Bricks = extract(&total_bricks, tempdir);
        if (Bricks == NULL) break; /* no more levels */
        score = 0; /* init score */
        prev_score = 1;

        /* init ball for next level */
        initball((SIZE_X / 2), (SIZE_Y / 2), 0, 0.5, 0.7);
        /* init platform for next level */
        initplaform((SIZE_X / 2) - 5, SIZE_Y - 4, (SIZE_X / 2) + 5);

        sprintf(print_lvl, "%s", df->d_name);   /* update level name */

        for(;;) {   /* game loop */
            if (current_key == -1 || touchedGrd) break;
            if ((score += collision()) != prev_score) {
                prev_score = score;
                sprintf(print_score, "Score: %d", score);

                if (score < 4)
                    Ball.speed += BALL_SPEED_INC;
            }
            compute();
            to_buff();

            print_buff(buff, print_lvl, 0, SIZE_Y - 3);
            print_buff(buff, print_score, 0, SIZE_Y - 2);

            draw();

            if (score == total_bricks)
                break;  /* all bricks destroyed */
            usleep(50000);
        }
        strcpy(tempdir, dirName);
        total_score += score;
        if (current_key == -1 || touchedGrd) break;
    }
    sprintf(print_score, "Score: %d", total_score);
    print_buff(buff, print_score, SIZE_X/2, SIZE_Y/2);
    draw();

    closedir(dr);
    free(buff);
    if (Bricks != NULL) free(Bricks);
    restoreMode();
}
