#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main()
{
	int	fd;
	char	*str;
	int		i;
	int		min;
	int		min2;
	int		max2;
	int	pair;
	int		max;

	pair = 0;
	fd = open("input", O_RDONLY);
	while(1)
	{
		i = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		while(*str != '-')
		{
			i = i * 10 + *str - 48;
			str++;
		}
		min = i;
		str++;
		i = 0;
		while(*str != ',')
		{
			i = i * 10 + *str - 48;
			str++;
		}
		max = i;
		str++;
		i = 0;
		while(*str != '-')
		{
			i = i * 10 + *str - 48;
			str++;
		}
		min2 = i;
		str++;
		i = 0;
		while(*str != '\n' && *str != '\0')
		{
			i = i * 10 + *str - 48;
			str++;
		}
		max2 = i;
		if (min2 >= min && min2 <= max)
			pair++;
		else if (max2 >= min && max2 <= max)
			pair++;
		else if (min >= min2 && min <= max2)
			pair++;
		else if (max >= min2 && max <= max2)
			pair++;
	}
	printf("%d\n", pair);
}