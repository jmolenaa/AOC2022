#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

char	**make_empty_grid(int maxx, int maxy)
{
	char	**grid;
	int		i = 0;

	grid = (char **)ft_calloc(maxy + 1, sizeof(char *));
	while (i < maxy)
	{
		*(grid + i) = (char *)ft_calloc(maxx + 1, sizeof(char));
		ft_memset(*(grid + i), '.', maxx);
		i++;
	}
	return (grid);

}

int	find_maximum_depth(int fd)
{
	char	*str;
	int		i;
	int		maxy = 0;

	lseek(fd, 0, SEEK_SET);
	while(1)
	{
		i = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		while (*(str + i) != '\0')
		{
			if (*(str + i) == ',')
			{
				if (maxy < ft_atoi(str + i + 1))
					maxy = ft_atoi(str + i + 1);
			}
			i++;
		}
	}
	return (maxy);
}

int	find_minimum_width(fd)
{
	char	*str;
	int		i;
	int		minx = 600;

	lseek(fd, 0, SEEK_SET);
	while(1)
	{
		i = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (minx > ft_atoi(str))
			minx = ft_atoi(str);
		while (*(str + i) != '\0')
		{
			if (*(str + i) == '>')
			{
				if (minx > ft_atoi(str + i + 1))
					minx = ft_atoi(str + i + 1);
			}
			i++;
		}
	}
	return (minx);
}

int	find_maximum_width(fd)
{
	char	*str;
	int		i;
	int		maxx = 0;

	lseek(fd, 0, SEEK_SET);
	while(1)
	{
		i = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (maxx < ft_atoi(str))
			maxx = ft_atoi(str);
		while (*(str + i) != '\0')
		{
			if (*(str + i) == '>')
			{
				if (maxx < ft_atoi(str + i + 1))
					maxx = ft_atoi(str + i + 1);
			}
			i++;
		}
	}
	return (maxx);
}

void	make_line_y(t_grid grid, int beginx, int beginy, int endy)
{
	if (beginy > endy)
	{
		while (beginy >= endy)
		{
			*(*(grid.cave + beginy) + beginx) = '#';
			beginy--;
		}
	}
	else
	{
		while (beginy <= endy)
		{
			*(*(grid.cave + beginy) + beginx) = '#';
			beginy++;
		}
	}
}

void	make_line_x(t_grid grid, int beginy, int beginx, int endx)
{
	if (beginx > endx)
	{
		while (beginx >= endx)
		{
			*(*(grid.cave + beginy) + beginx) = '#';
			beginx--;
		}
	}
	else
	{
		while (beginx <= endx)
		{
			*(*(grid.cave + beginy) + beginx) = '#';
			beginx++;
		}
	}
}

void	draw_rock_line(t_grid grid, char *str)
{
	int	beginx;
	int	beginy;
	int	endx;
	int	endy;

	sscanf(str, "%d,%d -> %d,%d", &beginx, &beginy, &endx, &endy);
	beginx = beginx - grid.minx;
	endx = endx - grid.minx;
	// printf("%d %d %d %d\n", beginx, beginy, endx, endy);
	if (beginx == endx)
		make_line_y(grid, beginx, beginy, endy);
	else
		make_line_x(grid, beginy, beginx, endx);
}

void	add_rocks(int fd, t_grid grid)
{
	char	*str;
	char	*rockline;
	int		i;
	int		j;
	
	lseek(fd, 0, SEEK_SET);
	while (1)
	{
		i = 0;
		j = 0;
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		while (*(str + i) != '\0')
		{
			if (*(str + i) == '>')
			{
				draw_rock_line(grid, str + j);
				j = i + 1;
			}
			i++;
		}
	}
}

t_grid	make_grid(void)
{
	t_grid	grid;
	int		fd = open("input", O_RDONLY);
	grid.maxx = find_maximum_width(fd);
	grid.minx = find_minimum_width(fd) - 1;
	int		maxx = grid.maxx - grid.minx + 2; 
	grid.maxy = find_maximum_depth(fd) + 2;
	// printf("%d, %d\n", find_maximum_width(fd), find_minimum_width(fd));
	// printf("%d, %d\n", grid.maxy, maxx);
	grid.cave = make_empty_grid(maxx, grid.maxy);
	add_rocks(fd, grid);
	// ft_print_grid(grid.cave);
	return (grid);
}