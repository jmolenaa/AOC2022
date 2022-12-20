#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

void	printpos(int *headpos, int *tailpos)
{
	printf("head : %d, %d\ntail : %d, %d\n", *headpos, *(headpos + 1), *tailpos, *(tailpos + 1));
}

void	printgrid(char **str)
{
	int	i = 0;

	while (i < 1000)
	{
		printf("%s\n", *(str + i));
		i++;
	}
	printf("\n");
}

char	**makegrid(void)
{
	char	**str;
	int		i = 0;

	str = (char **)malloc(1000 * 8);
	while (i < 1000)
	{
		*(str + i) = (char *)ft_calloc(1001, 1);
		ft_memset(*(str + i), '0', 1000);
		// printf("%s\n", *(str + i));
		i++;
	}
	return (str);
}

void	get_ver_and_hor(char *instructions, int *hor, int *ver)
{
	if (*instructions == 'R')
	{
		*hor = 1;
		*ver = 0;
	}
	else if (*instructions == 'L')
	{
		*hor = -1;
		*ver = 0;
	}
	else if (*instructions == 'U')
	{
		*hor = 0;
		*ver = -1;
	}
	else
	{
		*hor = 0;
		*ver = 1;
	}
}

void	change_head_tail(int *headpos, int *tailpos, int hor, int ver)
{
	int	temp[2];

	*temp = *headpos;
	*(temp + 1) = *(headpos + 1);
	*headpos = *headpos + ver;
	*(headpos + 1) = *(headpos + 1) + hor;
	if (*headpos - *tailpos < -1 || *headpos - *tailpos > 1)
	{
		*tailpos = *temp;
		*(tailpos + 1) = *(temp + 1);
	}
	else if (*(headpos + 1) - *(tailpos + 1) < -1 || *(headpos + 1) - *(tailpos + 1) > 1)
	{
		*tailpos = *temp;
		*(tailpos + 1) = *(temp + 1);
	}
}

void	adjustgrid(char **str, int fd, int *headpos, int *tailpos)
{
	char	*instructions;
	int		hor;
	int		ver;
	int		amountofsteps;

	while (1)
	{
		instructions = get_next_line(fd);
		if (instructions == (NULL))
			break ;
		get_ver_and_hor(instructions, &hor, &ver);
		// printf("%s\n", instructions);
		sscanf(instructions, "%*c %d", &amountofsteps);
		while (amountofsteps > 0)
		{
			change_head_tail(headpos, tailpos, hor, ver);
			// printf("%d, %d\n", *tailpos, *(tailpos + 1));
			// printpos(headpos, tailpos);
			*(*(str + *tailpos) + *(tailpos + 1)) = '1';
			amountofsteps--;
		}
	}
	// printgrid(str);
}

void	readpositions(char **str)
{
	int	i=0;
	int	j=0;
	int	count=0;

	while (j < 1000)
	{
		i = 0;
		while (i <1000)
		{
			if (*(*(str + j) + i) == '1')
				count++;
			i++;
		}
		j++;
	}
	printf("count : %d\n", count);
}

int	main()
{
	char	**str;
	int		headpos[2] = {500, 500};
	int		tailpos[2] = {500, 500};
	str = makegrid();
	// *(*(str + 1) + 5) = '1';
	// printgrid(str);

	// printpos(headpos, tailpos);
	int fd = open("input", O_RDONLY);
	adjustgrid(str, fd, headpos, tailpos);
	readpositions(str);
}