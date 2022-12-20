
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


int	main()
{
	char	*str;
	int	prio;
	int	i;
	char	c;
	int		j;
	int		x;

	prio = 0;
	while(1)
	{
		i = 0;
		str = get_next_line(0);
		// printf("%s\n", str);
		if (str == (NULL))
			break ;
		while(*(str + i) != '\0' && *(str + i) != '\n')
			i++;
		i = i / 2 ;
		// printf("%d\n", i);
		x = 0;
		c = '\0';
		while(x < i)
		{
			j = 0;
			while(j < i)
			{
				if (*(str + x) == *(str + i + j))
				{
					c = *(str + x);
					break;
				}
				j++;
			}
			x++;
		}
		if (c >= 'a' && c<= 'z')
			prio = prio + c - 'a' + 1;
		else
			prio = prio + c - 'A' + 27;
		// printf("%d\n", prio);
	}
	printf("%d\n", prio);
}