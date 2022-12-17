#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

int	main()
{
	char	*str;
	long long int		diff;
	long long int		repeats = 0;
	long long int		repeatdiff = 0;
	int fd = open("check", O_RDONLY);
	char	*firstdiff = get_next_line(fd);
	long long int	actual_height;
	while (1)
	{
		str = get_next_line(fd);
		if (ft_strchr(str, '/') != NULL)
			break ;
		sscanf(str, "%*d : %lld", &diff);
		repeatdiff = repeatdiff + diff;
		repeats++;
	}
	long long int	amountofrepeats = 1000000 / repeats;
	sscanf(firstdiff, "%*d : %lld", &diff);
	actual_height = amountofrepeats * repeatdiff + diff;
	int i = 1;
	while (amountofrepeats * repeats + i < 1000000)
	{
		sscanf(str, "%*d : %lld", &diff);
		actual_height = actual_height + diff;
		str = get_next_line(fd);
		i++;
	}
	printf("height : %lld\n", actual_height);
}