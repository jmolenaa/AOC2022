#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "struct.h"

void	printgrid(char **elev)
{
	int	i = 0;
	
	while (*(elev + i) != NULL)
	{
		printf("%s\n", *(elev + i));
		i++;
	}
	printf("\n");
}

void	printposition(int position[2])
{
	printf("%d %d\n", *position, *(position + 1));
}

t_grid	make_grid(void)
{
	char	*str;
	t_grid	grid;
	int fd = open("input", O_RDONLY);
	int i = 0;

	grid.rows = 0;
	while (get_next_line(fd))
		grid.rows++;
	grid.elev = (char **)ft_calloc(grid.rows + 1, sizeof(char *));
	lseek(fd, 0 , SEEK_SET);
	while (i < grid.rows)
		*(grid.elev + i++) = ft_strtrim(get_next_line(fd), "\n");
	grid.collumns = ft_strlen(*grid.elev);
	return (grid);	
}

void	get_start_end(t_grid *grid)
{
	int	j = 0;
	int	i = 0;

	while (*(grid->elev + j) != NULL)
	{
		i = 0;
		while (*(*(grid->elev + j) + i) != '\0')
		{
			if (*(*(grid->elev + j) + i) == 'S')
			{
				*(grid->start) = j;
				*(grid->start + 1) = i;

			}
			else if (*(*(grid->elev + j) + i) == 'E')
			{
				*(grid->end) = j;
				*(grid->end + 1) = i;
			}
			i++;
		}
		j++;
	}
}

void	change_start_end(t_grid *grid)
{
	grid->elev[grid->start[0]][grid->start[1]] = 'a';
	grid->elev[grid->end[0]][grid->end[1]] = 'z';

}

t_store	*make_new_loc(int j, int i, int steps)
{
	t_store	*new;

	new = (t_store *)malloc(sizeof(t_store));
	new->y = j;
	new->x = i;
	new->steps = steps;
	new->next = NULL;
	return (new);
}

void	put_loc_back(t_store **end_loc, t_store *prev_loc)
{
	t_store *temp;

	temp = *end_loc;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = prev_loc;
}

int	check_j_i(int j, int i, t_store *end_loc)
{
	while (end_loc != NULL)
	{
		if (end_loc->y == j && end_loc->x == i)
			return (0);
		end_loc = end_loc->next;
	}
	return (1);
}

void	make_new_locations(t_grid grid, int j, int i, int steps, t_store *end_loc)
{
	if (i > 0 && grid.elev[j][i - 1] - grid.elev[j][i] >= -1)
	{
		if (check_j_i(j, i - 1, end_loc))
			put_loc_back(&end_loc, make_new_loc(j, i - 1, steps));
	}
	if (j > 0 && grid.elev[j - 1][i] - grid.elev[j][i] >= -1)
	{
		if (check_j_i(j - 1, i, end_loc))
			put_loc_back(&end_loc, make_new_loc(j - 1, i, steps));
	}
	if (j < grid.rows - 1 && grid.elev[j + 1][i] - grid.elev[j][i] >= -1)
	{
		if (check_j_i(j + 1, i, end_loc))
			put_loc_back(&end_loc, make_new_loc(j + 1, i, steps));
	}
	if (i < grid.collumns - 1 && grid.elev[j][i + 1] - grid.elev[j][i] >= -1)
	{
		if (check_j_i(j, i + 1, end_loc))
			put_loc_back(&end_loc, make_new_loc(j, i + 1, steps));
	}
}

int	travel(t_grid grid, int j, int i)
{
	t_store *end_loc;
	t_store *temp;
	int		steps = 0;

	end_loc = make_new_loc(j, i, steps);
	temp = end_loc;
	while (1)
	{
		while (temp != NULL && temp->steps == steps)
		{
			j = temp->y;
			i = temp->x;
			if (*(*(grid.elev + j) + i) == 'a')
				return (steps);
			make_new_locations(grid, j, i, steps + 1, end_loc);
			temp = temp->next;
		}
		steps++;
	}
}

int	main()
{
	t_grid	grid;
	grid = make_grid();
	get_start_end(&grid);
	change_start_end(&grid);
	// printf("%d, %d\n", *grid.end, *(grid.end + 1));
	// printf("%d, %d\n", grid.rows, grid.collumns);
	int stepmin = travel(grid, *grid.end, *(grid.end + 1));
	printf("minimum amount of steps : %d\n", stepmin);
}