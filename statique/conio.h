#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#ifndef CONIO_H_INCLUDED
#define CONIO_H_INCLUDED

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

#endif // CONIO_H_INCLUDED
