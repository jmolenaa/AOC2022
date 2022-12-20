#include <stdio.h>
// #include <fctnl.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
    char *str;
    int fd;
    int totalscore;

    totalscore = 0;
    while(1)
    {
        str = get_next_line(0);
        if (str == NULL)
            break ;
        totalscore = totalscore + *(str + 2) - 87;
        if (*str == 'A')
        {
            if (*(str + 2) == 'X')
                totalscore = totalscore + 3;
            else if (*(str + 2) == 'Y')
                totalscore = totalscore + 6;
        }
        if (*str == 'B')
        {
            if (*(str + 2) == 'Y')
                totalscore = totalscore + 3;
            else if (*(str + 2) == 'Z')
                totalscore = totalscore + 6;
        }
        if (*str == 'C')
        {
            if (*(str + 2) == 'Z')
                totalscore = totalscore + 3;
            else if (*(str + 2) == 'X')
                totalscore = totalscore + 6;
        }
    }
    printf("%d\n", totalscore);
}
