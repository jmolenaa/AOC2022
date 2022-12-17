#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	printrocks(t_rocks *firstrock)
{
	for(int i = 0; i < 20; i++)
	{
		printf("rock %d\nis %d tall\nand looks\n", firstrock->rockid, firstrock->ymax);
		ft_print_grid(firstrock->rock);
		printf("\n");
		firstrock = firstrock->nextrock;
	}
}

t_chamber	*make_chamber(void)
{
	t_chamber	*chamber = malloc(sizeof(t_chamber));
	chamber->ymax = 4000;
	chamber->chamber = ft_calloc(chamber->ymax + 1, sizeof(char *));
	chamber->currentheight = chamber->ymax - 1;
	chamber->ymax = chamber->currentheight;
	*(chamber->chamber + chamber->ymax) = ft_strdup("+@@@@@@@+");
	for (int i = 0; i < chamber->ymax; i++)
		*(chamber->chamber + i) = ft_strdup("@.......@");
	return (chamber);
}

void	put_rock_in_chamber(t_rocks *rocks, t_chamber *chamber)
{
	for (int i = 0; i < rocks->ymax; i++)
	{
		ft_strcpynonull(*(chamber->chamber + chamber->currentheight - 4 - i) + 3,\
		 *(rocks->rock + rocks->ymax - 1 - i));
	}
	chamber->rockheight = rocks->ymax - 1;
	chamber->bottomrock = chamber->currentheight - 4;
	chamber->rockid = rocks->rockid;
	chamber->leftrock = 3;
	chamber->rockwidth = ft_strlen(*rocks->rock) - 1;
}

int	check_left(t_chamber *chamber)
{
	for (int i = 0; i <= chamber->rockheight; i++)
	{
		for (int j = 0; *(*(chamber->chamber + chamber->bottomrock - i) + j) != '\0'; j++)
		{
			if (*(*(chamber->chamber + chamber->bottomrock - i) + j) == '#' &&\
			*(*(chamber->chamber + chamber->bottomrock - i) + j - 1) == '@')
				return (0);
		}
	}
	return (1);
}

void	move_left(t_chamber *chamber)
{
	if (check_left(chamber))
	{
		for (int i = 0; i <= chamber->rockheight; i++)
		{
			for (int j = 0; *(*(chamber->chamber + chamber->bottomrock - i) + j) != '\0'; j++)
			{
				if (*(*(chamber->chamber + chamber->bottomrock - i) + j) == '#')
				{
					*(*(chamber->chamber + chamber->bottomrock - i) + j - 1) = '#';
					*(*(chamber->chamber + chamber->bottomrock - i) + j) = '.';
				}
			}
		}
		chamber->leftrock = chamber->leftrock - 1;
	}
}

int	check_right(t_chamber *chamber)
{
	for (int i = 0; i <= chamber->rockheight; i++)
	{
		for (int j = 0; *(*(chamber->chamber + chamber->bottomrock - i) + j) != '\0'; j++)
		{
			if (*(*(chamber->chamber + chamber->bottomrock - i) + j) == '#' &&\
			*(*(chamber->chamber + chamber->bottomrock - i) + j + 1) == '@')
				return (0);
		}
	}
	return (1);
}

void	move_right(t_chamber *chamber)
{
	if (check_right(chamber))
	{
		for (int i = 0; i <= chamber->rockheight; i++)
		{
			for (int j = 7; j >= 0; j--)
			{
				if (*(*(chamber->chamber + chamber->bottomrock - i) + j) == '#')
				{
					*(*(chamber->chamber + chamber->bottomrock - i) + j + 1) = '#';
					*(*(chamber->chamber + chamber->bottomrock - i) + j) = '.';
				}
			}
		}
		chamber->leftrock = chamber->leftrock + 1;
	}
}

void	move_rock_horizontally(t_chamber *chamber, t_jet *jet)
{
	if (*(jet->jetpattern) == '\0')
		jet->jetpattern = jet->begin;
	if (*jet->jetpattern == '<')
		move_left(chamber);
	else
		move_right(chamber);
	jet->jetpattern++;
}

int	check_below(t_chamber *chamber)
{
	int	i = 0;
	while (*(*(chamber->chamber + chamber->bottomrock) + i) != '\0')
	{
		if (*(*(chamber->chamber + chamber->bottomrock) + i) == '#' &&\
		 *(*(chamber->chamber + chamber->bottomrock + 1) + i) == '@')
		 	return (1);
		i++;
	}
	i = 0;
	if (chamber->rockid == 2)
	{
		while (*(*(chamber->chamber + chamber->bottomrock - 1) + i) != '\0')
		{
			if (*(*(chamber->chamber + chamber->bottomrock - 1) + i) == '#' &&\
			*(*(chamber->chamber + chamber->bottomrock) + i) == '@')
				return (1);
			i++;
		}
	}
	return (0);
}

void	move_rock_down(t_chamber *chamber, t_rocks *rocks)
{
	for (int i = 0; i <= chamber->rockheight; i++)
	{
		for (int j = 0; j <= chamber->rockwidth ; j++)
		{
			if (*(*(chamber->chamber + chamber->bottomrock - i + 1) + chamber->leftrock + j) == '@')
				continue ;
			else
				*(*(chamber->chamber + chamber->bottomrock - i + 1) + chamber->leftrock + j) = \
				*(*(chamber->chamber + chamber->bottomrock - i) + chamber->leftrock + j);
		}
	}
	for (int i = 0; i <= chamber->rockwidth; i++)
	{
		if (*(*(chamber->chamber + chamber->bottomrock - chamber->rockheight) + chamber->leftrock + i) == '@')
				continue ;
		*(*(chamber->chamber + chamber->bottomrock - chamber->rockheight) + chamber->leftrock + i) = '.';
	}
	chamber->bottomrock = chamber->bottomrock + 1;
}

void	solidify_rock(t_chamber *chamber)
{
	for (int i = 0; i <= chamber->rockheight; i++)
	{
		for (int j = 0; *(*(chamber->chamber + chamber->bottomrock - i) + j) != '\0'; j++)
		{
			if (*(*(chamber->chamber + chamber->bottomrock - i) + j) == '#')
				*(*(chamber->chamber + chamber->bottomrock - i) + j) = '@';
		}
	}
}

void	let_rocks_fall(t_jet *jet, t_rocks *rocks, t_chamber *chamber)
{
	char	*temp;
	for (int i = 0; i < 2022; i++)
	{
		temp = jet->jetpattern;
		put_rock_in_chamber(rocks, chamber);
		while (1)
		{
			move_rock_horizontally(chamber, jet);
			if (check_below(chamber))
				break ;
			move_rock_down(chamber, rocks);
		}
		solidify_rock(chamber);
		if (chamber->bottomrock - chamber->rockheight <= chamber->currentheight)
			chamber->currentheight = chamber->bottomrock - chamber->rockheight;
		rocks = rocks->nextrock;
	}
	ft_print_grid(chamber->chamber);
	printf("rock height\n%d\n", chamber->ymax - chamber->currentheight);
	// printf("%s\n", temp);
}

int	main()
{
	t_jet		*jet;
	t_rocks		*firstrock;
	t_chamber	*chamber;

	jet = get_jet_pattern();
	firstrock = get_rocks();
	chamber = make_chamber();
	let_rocks_fall(jet, firstrock, chamber);
}
