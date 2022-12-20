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
        if (*(str + 2) == 'X')
        {
            if (*(str) == 'A')
                totalscore = totalscore + 3;
            else if (*(str) == 'B')
                totalscore = totalscore + 1;
			else if (*(str) == 'C')
                totalscore = totalscore + 2;
        }
       else if (*(str + 2) == 'Y')
        {
			totalscore = totalscore + 3;
            if (*(str) == 'A')
                totalscore = totalscore + 1;
            else if (*(str) == 'B')
                totalscore = totalscore + 2;
			else if (*(str) == 'C')
                totalscore = totalscore + 3;
        }
		else if (*(str + 2) == 'Z')
        {
			totalscore = totalscore + 6;
            if (*(str) == 'A')
                totalscore = totalscore + 2;
            else if (*(str) == 'B')
                totalscore = totalscore + 3;
			else if (*(str) == 'C')
                totalscore = totalscore + 1;
        }
    }
    printf("%d\n", totalscore);
}
