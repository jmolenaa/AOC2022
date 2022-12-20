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

void	countedges(t_grid *grid)
{
	grid->visibletrees = grid->rows * 2 + (grid->columns * 2 - 4);
}

int	checkleft(t_grid grid, int i, int j)
{
	int	left;

	left = i - 1;
	while (left >= 0)
	{
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + j) + left))
			return (0);
		left--;
	}
	return (1);
}

int	checkright(t_grid grid, int i, int j)
{
	int	right;

	right = i + 1;
	while (right < grid.columns)
	{
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + j) + right))
			return (0);
		right++;
	}
	return (1);
}

int	checkup(t_grid grid, int i, int j)
{
	int	up;

	up = j - 1;
	while (up >= 0)
	{
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + up) + i))
			return (0);
		up--;
	}
	return (1);
}

int	checkdown(t_grid grid, int i, int j)
{
	int	down;

	down = j + 1;
	while (down < grid.rows)
	{
		if (*(*(grid.trees + j) + i) <= *(*(grid.trees + down) + i))
			return (0);
		down++;
	}
	return (1);
}

void	countinterior(t_grid *grid)
{
	int	i = 1;
	int	j = 1;

	while (j < grid->rows - 1)
	{
		i = 1;
		while (i < grid->columns - 1)
		{
			if (checkleft(*grid, i, j) || checkright(*grid, i, j) || checkup(*grid, i, j) || checkdown(*grid, i, j))
				grid->visibletrees++;
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
	grid.visibletrees = 0;
	// printgrid(grid);
	countedges(&grid);
	countinterior(&grid);
	printf("%d\n", grid.visibletrees);

}