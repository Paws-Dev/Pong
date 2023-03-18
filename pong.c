#include <stdio.h>

int l_racket_y = 12;
int l_racket_y_u = 13;
int l_racket_y_l = 11;
int r_racket_y = 12;
int r_racket_y_u = 13;
int r_racket_y_l = 11;
int ball_x = 40;
int ball_y = 12;
char input;
int dir = 1;
int started = 0;
int scoreL = 0;
int scoreR = 0;

void reset() {
    l_racket_y = 12;
    l_racket_y_u = 13;
    l_racket_y_l = 11;
    r_racket_y = 12;
    r_racket_y_u = 13;
    r_racket_y_l = 11;
    ball_x = 40;
    ball_y = 12;
    dir = 2;
}

int object(int x, int y) {
    char obj = ' ';
    if (y == l_racket_y && x == 0)
        obj = '|';
    if (y == l_racket_y_u && x == 0)
        obj = '|';
    if (y == l_racket_y_l && x == 0)
        obj = '|';

    if (y == r_racket_y && x == 80)
        obj = '|';
    if (y == r_racket_y_u && x == 80)
        obj = '|';
    if (y == r_racket_y_l && x == 80)
        obj = '|';

    if (x == 40)
        obj = '|';
    if (y == 26)
        obj = '#';
    if (y == -1)
        obj = '#';
    if (y == -1 && x == 34)
        obj = ' ';
    if (y == -1 && x == 36)
        obj = ' ';
    if (y == -1 && x == 37)
        obj = ' ';
    if (y == -1 && x == 38)
        obj = 'S';
    if (y == -1 && x == 39)
        obj = 'C';
    if (y == -1 && x == 40)
        obj = 'O';
    if (y == -1 && x == 41)
        obj = 'R';
    if (y == -1 && x == 42)
        obj = 'E';
    if (y == -1 && x == 43)
        obj = ' ';
    if (y == -1 && x == 44)
        obj = ' ';
    if (y == -1 && x == 46)
        obj = ' ';
    if (x == ball_x && y == ball_y)
        obj = '*';
    if (y == -1 && x == 45) {
        printf("%d", scoreR);
        return 0;
    }
    if (y == -1 && x == 35) {
        printf("%d", scoreL);
        return 0;
    }

    printf("%c", obj);
    return 0;
}

void render() {
    for (int y = -1; y <= 26; y++) {
        for (int x = 0; x <= 80; x++) {
            object(x, y);
        }
        printf("\n");
    }

    printf("INPUT SPACE TO START GAME\nINPUT");
    printf("'A'/'Z' TO MOVE LEFT RACKET \nINPUT 'K'/'M'");
    printf("TO MOVE RIGHT RACKET\nINPUT 'Q' TO ABORT GAME\n");
}

void move() {
    if (ball_y == 0) {
        if (dir == 1)
            dir = 4;
        if (dir == 2)
            dir = 3;
    }

    if (ball_y == 25) {
        if (dir == 3)
            dir = 2;
        if (dir == 4)
            dir = 1;
    }

    if (ball_x == 0) {
        if (ball_y == l_racket_y || ball_y == l_racket_y_u || ball_y == l_racket_y_l) {
            if (dir == 1)
                dir = 2;
            if (dir == 4)
                dir = 3;
        } else {
            reset();
            scoreL++;
        }
    }

    if (ball_x == 80) {
        if (ball_y == r_racket_y || ball_y == r_racket_y_u || ball_y == r_racket_y_l) {
            if (dir == 3)
                dir = 4;
            if (dir == 2)
                dir = 1;
        } else {
            reset();
            scoreR++;
        }
    }

    if (dir == 1) {
        ball_x--;
        ball_y--;
    }

    if (dir == 4) {
        ball_x--;
        ball_y++;
    }

    if (dir == 3) {
        ball_x++;
        ball_y++;
    }

    if (dir == 2) {
        ball_x++;
        ball_y--;
    }
}

void y_add(char c) {
    if (c == 'L') {
        l_racket_y_u = l_racket_y + 1;
        l_racket_y_l = l_racket_y - 1;
    }

    if (c == 'R') {
        r_racket_y_u = r_racket_y + 1;
        r_racket_y_l = r_racket_y - 1;
    }
}

int main() {
    while (1) {
        render();
        if (started == 0) {
            printf(" INPUT SPACE TO START");
            scanf("%c", & input);
            if (input == 32)
                started = 1;
            else
                printf("\33c\e[3J");
        }

        if (started == 1) {
            if (scoreL == 21) {
                printf("\33c\e[3J");
                printf(" CONGRATULATIONS TO LEFT PLAYER, YOU ARE THE CHAMPION!!!!! ");
                break;
            }
            if (scoreR == 21) {
                printf("\33c\e[3J");
                printf(" CONGRATULATIONS TO RIGHT PLAYER, YOU ARE THE CHAMPION!!!!! ");
                break;
            }

            scanf("%c", & input);
            printf("\33c\e[3J");

            if (input == 'a' && l_racket_y != 1) {
                l_racket_y--;
                y_add('L');
            }

            if (input == 'z' && l_racket_y != 24) {
                l_racket_y++;
                y_add('L');
            }

            if (input == 'k' && r_racket_y != 1) {
                r_racket_y--;
                y_add('R');
            }
            if (input == 'm' && r_racket_y != 24) {
                r_racket_y++;
                y_add('R');
            }

            if (input == 'q') {
                printf("\33c\e[3J");
                printf("THANK YOU FOR PLAYING!!!!\nBYE-BYE ");
                break;
            }

            move();
        }
    }
}

