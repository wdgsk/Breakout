#include "headers.h"

struct termios initial;
short current_key = 0;

void *input (void *arg) /* thread input */
{
    do {
        read(STDIN_FILENO, &current_key, 1);

        if (current_key == 'q') { /* exit */
            current_key = -1;
            pthread_exit(NULL);
        }
    } while (1);
}

void enableRawMode(void) /* disable output */
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &initial);
    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void restoreMode(void) /* restore default terminal flags */
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &initial);
}
