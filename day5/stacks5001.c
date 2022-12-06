#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

void	printstacks(char **stacks)
{
	int	i = 0;
	while (*(stacks + i) != NULL)
	{
		printf("%s\n", *(stacks + i));
		i++;
	}
}

char	**putinstacks(char **stacks)
{
	int	i;
	i = 0;
	stacks = (char **)ft_calloc(10, 8);
	while (i < 9)
	{
		*(stacks + i) = (char *)ft_calloc(1000, 1);
		i++;
	}
	ft_strlcpy(*(stacks + 0), "JHGMZNTF", 9);
	ft_strlcpy(*(stacks + 1), "VWJ", 9);
	ft_strlcpy(*(stacks + 2), "GVLJBTH", 9);
	// ft_strlcpy(*(stacks + 0), "ZN", 9);
	// ft_strlcpy(*(stacks + 1), "MCD", 9);
	// ft_strlcpy(*(stacks + 2), "P", 9);
	ft_strlcpy(*(stacks + 3), "BPJNCDVL", 9);
	ft_strlcpy(*(stacks + 4), "FWSMPRG", 9);
	ft_strlcpy(*(stacks + 5), "GHCFBNVM", 9);
	ft_strlcpy(*(stacks + 6), "DHGMR", 9);
	ft_strlcpy(*(stacks + 7), "HNMVZD", 9);
	ft_strlcpy(*(stacks + 8), "GNFH", 9);
	return (stacks);
}

int	gethowmany(char *str)
{
	while (*str < '0' || *str > '9')
		str++;
	return (ft_atoi(str));
}

int	getfrom(char *str)
{
	while (*str < '0' || *str > '9')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str < '0' || *str > '9')
		str++;
	return (ft_atoi(str));
}

int	getto(char *str)
{
	while (*str < '0' || *str > '9')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str < '0' || *str > '9')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str < '0' || *str > '9')
		str++;
	return (ft_atoi(str));
}

char	**movestacks(char **stacks, int howmany, int from, int to)
{
	int	i = 0;

	int fromlen = ft_strlen(*(stacks + from));
	int tolen = ft_strlen(*(stacks + to));
	while (i < howmany)
	{
		*(*(stacks + to) + tolen + i) = *(*(stacks + from) + fromlen - howmany + i);
		*(*(stacks + from) + fromlen - howmany + i) = '\0';
		i++;
	}
	return (stacks);
}

void	getoutput(char **stacks)
{
	int	i = 0;
	int len;
	while (i < 9)
	{
		len = ft_strlen(*(stacks + i));
		printf("%c", *(*(stacks + i) + len - 1));
		i++;
	}
}

int	main()
{
	char	*str;
	int fd = open("input", O_RDONLY);
	char	**stacks;

	while(1)
	{
		str = get_next_line(fd);
		if (*str == '\n')
			break ;
	}
	stacks = NULL;
	stacks = putinstacks(stacks);
	while(1)
	{
		str = get_next_line(fd);
		if (str == (NULL))
			break ;
		int	howmany = gethowmany(str);
		int	from = getfrom(str) - 1;
		int to = getto(str) - 1;
		stacks = movestacks(stacks, howmany, from, to);
	}
	printstacks(stacks);
	getoutput(stacks);

}