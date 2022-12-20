#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"


int	comparechars(char *strcmp)
{
	int	i;

	i = 0;
	while (*(strcmp + i) != '\0')
	{
		if (ft_strchr(strcmp + i + 1, *(strcmp + i)) != (NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main()
{
	char	*str;
	int		i;
	int		onetofourteen;
	char	strcmp[15];

	int fd = open("test", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	onetofourteen = 0;
	*(strcmp + 14) = '\0';
	while (*(str + i) != '\0')
	{
		*(strcmp + onetofourteen) = *(str + i);
		if (i >= 13)
		{
			if (comparechars(strcmp) == 1)
				break ;
		}
		onetofourteen++;
		if (onetofourteen == 14)
			onetofourteen = 0;
		i++;
	}
	printf("%d\n", i + 1);
}
