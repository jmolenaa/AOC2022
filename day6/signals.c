#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main()
{
	char	*str;
	int		i;
	int		onetofour;

	int fd = open("input", O_RDONLY);
	str = get_next_line(fd);
	i = 3;
	while (*(str + i) != '\0')
	{
		if ((str[i] != str[i - 3] && str[i] != str[i - 2] && str[i] != str[i - 1])\
		&& (str[i - 1] != str[i - 3] && str[i - 1] != str[i - 2]) && str[i - 2] != str[i -3])
			break ;
		i++;
	}
	printf("%d\n", i + 1);
}
