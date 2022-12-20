
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"


int	main()
{
	char	*str;
	char	*str2;
	char	*str3;
	int	prio;
	int	i;
	char	c;
	int		j;
	int		x;

	prio = 0;
	while(1)
	{
		str = get_next_line(0);
		if (str == (NULL))
			break ;
		str2 = get_next_line(0);
		str3 = get_next_line(0);
		x = 0;
		c = '\0';
		while(*(str + x) != '\n')
		{
			j = 0;
			while(*(str2 + j) != '\n')
			{
				if (*(str + x) == *(str2 + j))
				{
					 i = 0;
					while (*(str3 + i) != '\n' && *(str3 + i) != '\0')
					{
						if (*(str3 + i) == *(str + x))
						{
							c = *(str + x);
							break ;
						}
						i++;
					}
				}
				j++;
				if (c != '\0')
					break ;
			}
			if (c != '\0')
				break ;
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