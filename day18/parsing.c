#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	printgrid(t_grid *grid)
{
	for (int z = 0; z < grid->zmax + 2; z++)
	{
		ft_print_grid(*(grid->grid + z));
		printf("\n");
	}
}

void	find_maxes(t_grid *grid, int fd)
{
	int		x = 0;
	int		y = 0;
	int		z = 0;
	grid->xmax = 0;
	grid->ymax = 0;
	grid->zmax = 0;

	for (char *str = get_next_line(fd); str != NULL; str = get_next_line(fd))
	{
		sscanf(str, "%d,%d,%d", &x, &y, &z);
		if (x > grid->xmax)
			grid->xmax = x;
		if (y > grid->ymax)
			grid->ymax = y;
		if (z > grid->zmax)
			grid->zmax = z;
	}
}

void	allocate_grid_and_fill(t_grid *grid, int fd)
{
	grid->grid = (char ***)ft_calloc(grid->zmax + 3, sizeof(char **));
	for (int z = 0; z < grid->zmax + 2; z++)
	{
		*(grid->grid + z) = (char **)ft_calloc(grid->ymax + 3, sizeof(char *));
		for (int y = 0; y < grid->ymax + 2; y++)
		{
			*(*(grid->grid + z) + y) = (char *)ft_calloc(grid->xmax + 3, sizeof(char));
			ft_memset(*(*(grid->grid + z) + y), '.', grid->xmax + 2);
		}
	}
}

t_grid	*make_grid(int fd)
{
	t_grid	*grid = malloc(sizeof(t_grid));
	find_maxes(grid, fd);
	lseek(fd, 0, SEEK_SET);
	allocate_grid_and_fill(grid, fd);
	lseek(fd, 0, SEEK_SET);
	// printf("%d, %d, %d\n", grid->xmax, grid->ymax, grid->zmax);
	return (grid);
}

void	fill_grid(int fd, t_grid *grid)
{
	int	x;
	int	y;
	int	z;

	for (char *str = get_next_line(fd); str != NULL; str = get_next_line(fd))
	{
		sscanf(str, "%d,%d,%d", &x, &y, &z);
		*(*(*(grid->grid + z) + y) + x) = '#';
	}
}

t_grid	*get_grid(void)
{
	t_grid	*grid;
	int	fd = open("input", O_RDONLY);

	grid = make_grid(fd);
	fill_grid(fd, grid);
	return (grid);
}