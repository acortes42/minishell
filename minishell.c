#include "minishell.h"

int obtain_full_line(int fd, char **parseString)
{
    write(1, "obta\n", 5);
    return (get_next_line(fd, parseString));
}

int execute (int  exceptionNum,char **parseString)
{
    write(1, "exec\n", 5);
    exceptionNum = 2;
    return (0);
}

int main(int argc, char **argv)
{
    char    **parseString;
    int     exceptionNum;

    exceptionNum = 1;
    write(1, "Init\n", 5);
    while (exceptionNum == 1)
    {
        write(1, "Init>", 5);
        obtain_full_line(1, parseString);
        execute(exceptionNum, parseString);
    }
    (void)argc;
    (void)argv;
    return (0);
}