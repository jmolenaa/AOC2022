#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
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
		i++;
	}
	return (str);
}

void	movediagonally(int knots[10][2], int i)
{
	if (*(*(knots + i - 1)) > *(*(knots + i)))
		*(*(knots + i)) = *(*(knots + i)) + 1;
	else
		*(*(knots + i)) = *(*(knots + i)) - 1;
	if (*(*(knots + i - 1) + 1) > *(*(knots + i) + 1))
		*(*(knots + i) + 1) = *(*(knots + i) + 1) + 1;
	else
		*(*(knots + i) + 1) = *(*(knots + i) + 1) - 1;
}

void	setknots(int knots[10][2], int *headpos)
{
	int	i=0;

	*(*(knots + i)) = *headpos;
	*(*(knots + i) + 1) = *(headpos + 1);
	i++;
	while (i < 10)
	{
		*(*(knots + i)) = 500;
		*(*(knots + i) + 1) = 500;
		i++;
	}
}

void	printknots(int knots[10][2])
{
	int	i =0;
	char	**str;

	str = makegrid();
	*(*(str + 50) + 50) = 'S';
	*(*(str + *(*(knots + i))) + *(*(knots + i) + 1)) = 'H';
	i++;
	while (i < 10)
	{
		*(*(str + *(*(knots + i))) + *(*(knots + i) + 1)) = i + 48;
		i++;
	}
	printgrid(str);
}

void	printkn(int knots[10][2])
{
	int	i =0;

	while (i < 9)
	{
		printf("%d : %d, %d\n", i, *(*(knots + i)), *(*(knots + i) + 1));
		i++;
	}
}

void	next_knot(int knots[10][2], int i)
{
	if (abs(*(*(knots + i - 1)) - *(*(knots + i))) > 1 || abs(*(*(knots + i - 1) + 1) - *(*(knots + i) + 1)) > 1)
	{
		if ((abs(*(*(knots + i - 1)) - *(*(knots + i))) > 0 && abs(*(*(knots + i - 1) + 1) - *(*(knots + i) + 1)) > 0))
			movediagonally(knots, i);
		else if (*(*(knots + i - 1)) - *(*(knots + i)) > 1)
			*(*(knots + i)) = *(*(knots + i)) + 1;
		else if (*(*(knots + i - 1)) - *(*(knots + i)) < -1)
			*(*(knots + i)) = *(*(knots + i)) - 1;
		else if (*(*(knots + i - 1) + 1) - *(*(knots + i) + 1) > 1)
			*(*(knots + i) + 1) = *(*(knots + i) + 1) + 1;
		else if (*(*(knots + i - 1) + 1) - *(*(knots + i) + 1) < -1)
			*(*(knots + i) + 1) = *(*(knots + i) + 1) - 1;
	}
	if (i < 9)
	{
		i++;
		next_knot(knots, i);
	}
}

void	change_position(int knots[10][2], char *instructions)
{
	int	i = 0;

	if (*instructions == 'R')
		*(*(knots + i) + 1) = *(*(knots + i) + 1) + 1;
	else if (*instructions == 'L')
		*(*(knots + i) + 1) = *(*(knots + i) + 1) - 1;
	else if (*instructions == 'U')
		*(*(knots + i)) = *(*(knots + i)) - 1;
	else if (*instructions == 'D')
		*(*(knots + i)) = *(*(knots + i)) + 1;
	i++;
	next_knot(knots, i);

}

void	adjustgrid(char **str, int fd, int *headpos)
{
	char	*instructions;
	int		hor;
	int		ver;
	int		amountofsteps;
	int		knots[10][2];

	setknots(knots, headpos);
	while (1)
	{
		instructions = get_next_line(fd);
		if (instructions == (NULL))
			break ;
		sscanf(instructions, "%*c %d", &amountofsteps);
		while (amountofsteps > 0)
		{
			change_position(knots, instructions);
			// printknots(knots);
			*(*(str + *(*(knots + 9))) + *(*(knots + 9) + 1)) = '1';
			amountofsteps--;
		}
		// printknots(knots);
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
	str = makegrid();
	// *(*(str + 1) + 5) = '1';

	// printpos(headpos, tailpos);
	int fd = open("input", O_RDONLY);
	adjustgrid(str, fd, headpos);
	// printgrid(str);
	readpositions(str);
}