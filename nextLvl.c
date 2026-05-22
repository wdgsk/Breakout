#include "headers.h"

#define MAX_DIGITS 3 /* number of 3 digits */

brick* extract(int* totalbricks, char* fileDir)
{
    char currLine[MAX_DIGITS];
    int numBricks;  /* number of bricks */
    brick* arr;

    FILE *file;
    file = fopen(fileDir, "r");

    if (!file) {
        fprintf(stderr, "Can't open file\n");
        return NULL;
    } else {
        fgets(currLine, 3, file);
        numBricks = atoi(currLine);
        *totalbricks = numBricks;

        /* hold bricks' info */
        arr = (brick*) malloc(numBricks * sizeof(brick));
    }

    int c;
    int wasBrick = 0;
    int index = 0;
    int x = 0, y = 0; /* iterate */

    if (file) {
        while ((c = getc(file)) != EOF) {
            //++x;
            if (c == '#' && wasBrick == 0) {
                wasBrick = 1;
                arr[index].init_x = x;
                arr[index].y = y;
            } else if (c == ' ' && wasBrick == 1) {
                arr[index].fin_x = x;
                ++index;
                wasBrick = 0;
                if (numBricks-- == 0) break;
            } else if (c == '\n' && wasBrick == 1) {
                arr[index].fin_x = x;
                ++index;
                ++y;
                wasBrick = 0;
                x = 0;
            }
            ++x;
        }
        fclose(file);
    }

    return arr;
}
