#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	printgrid(t_grid grid)
{
	int	j = 0;

	printf("rows :		%d\ncolumns :	%d\ngrid :\n\n", grid.rows, grid.columns);
	while (*(grid.trees + j) != NULL)
		printf("		%s\n", *(grid.trees + j++));
	// printf("%s\n", *(grid.trees + j));
}

int	countleft(t_grid grid, int i, int j)
{
	int	left;
	int	scenicscore = 0;

	left = i - 1;
	while (left >= 0)
	{
		scenicscore++;
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + j) + left))
			return (scenicscore);
		left--;
	}
	return (scenicscore);
}

int	countright(t_grid grid, int i, int j)
{
	int	right;
	int	scenicscore = 0;

	right = i + 1;
	while (right < grid.columns)
	{
		scenicscore++;
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + j) + right))
			return (scenicscore);
		right++;
	}
	return (scenicscore);
}

int	countup(t_grid grid, int i, int j)
{
	int	up;
	int scenicscore = 0;

	up = j - 1;
	while (up >= 0)
	{
		scenicscore++;
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + up) + i))
			return (scenicscore);
		up--;
	}
	return (scenicscore);
}

int	countdown(t_grid grid, int i, int j)
{
	int	down;
	int	scenicscore = 0;

	down = j + 1;
	while (down < grid.rows)
	{
		scenicscore++;
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + down) + i))
			return (scenicscore);
		down++;
	}
	return (scenicscore);
}

void	check_and_adjust_highest_count(t_grid *grid)
{
	int	totalscenicscore;

	totalscenicscore = grid->scenic_score_left * grid->scenic_score_right * grid->scenic_score_up * grid->scenic_score_down;
	if (totalscenicscore > grid->highestscenicscore)
		grid->highestscenicscore = totalscenicscore;
}

void	countscenicscores(t_grid *grid)
{
	int	i = 0;
	int	j = 0;

	while (j < grid->rows)
	{
		i = 0;
		while (i < grid->columns)
		{
			grid->scenic_score_left = countleft(*grid, i, j);
			grid->scenic_score_right = countright(*grid, i, j);
			grid->scenic_score_up = countup(*grid, i, j);
			grid->scenic_score_down = countdown(*grid, i, j);
			// printf("%d %i : %d, %d, %d, %d\n", j, i, grid->scenic_score_up, grid->scenic_score_left, grid->scenic_score_right, grid->scenic_score_down);
			check_and_adjust_highest_count(grid);
			i++;
		}
		j++;
	}

}

t_grid	makegrid(void)
{
	int		i = 0;
	int		j = 0;
	t_grid	grid;
	int		fd = open("input", O_RDONLY);

	grid.rows = 0;
	while (get_next_line(fd) != (NULL))
		grid.rows++;
	grid.trees = (char **)ft_calloc(grid.rows + 1, sizeof(char *));
	lseek(fd, 0 , SEEK_SET);
	while (j < grid.rows)
		*(grid.trees + j++) = ft_strtrim(get_next_line(fd), "\n");
	grid.columns = ft_strlen(*grid.trees);
	close(fd);
	return (grid);
}

int	main()
{
	t_grid	grid;

	grid = makegrid();
	// printgrid(grid);
	grid.highestscenicscore = 0;
	countscenicscores(&grid);
	printf("%d\n", grid.highestscenicscore);

}