#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

int	consider_blizzards_right(t_map *map, int x, int y, int steps)
{
	if (x + steps >= map->xmax - 1)
	{
		if (*(*(map->grid + y) + x - (map->xmax - 2) + steps) == '<')
			return (1);
	}
	else if (*(*(map->grid + y) + x + steps) == '<')
		return (1);
	return (0);
}

int	consider_blizzards_left(t_map *map, int x, int y, int steps)
{
	if (x - steps <= 0)
	{
		if (*(*(map->grid + y) + x + (map->xmax - 2) - steps) == '>')
			return (1);
	}
	else if (*(*(map->grid + y) + x - steps) == '>')
		return (1);
	return (0);
}

int	consider_blizzards_down(t_map *map, int x, int y, int steps)
{
	if (y + steps >= map->ymax - 1)
	{
		if (*(*(map->grid + y - (map->ymax - 2) + steps) + x) == '^')
			return (1);
	}
	else if (*(*(map->grid + y + steps) + x) == '^')
		return (1);
	return (0);
}

int	consider_blizzards_up(t_map *map, int x, int y, int steps)
{
	if (y - steps <= 0)
	{
		if (*(*(map->grid + y + (map->ymax - 2) - steps) + x) == 'v')
			return (1);
	}
	else if (*(*(map->grid + y - steps) + x) == 'v')
		return (1);
	return (0);
}

int	look_if_empty(t_map *map, int x, int y, int steps)
{
	if (consider_blizzards_right(map, x, y, steps % (map->xmax - 2)))
		return (0);
	if (consider_blizzards_left(map, x, y, steps % (map->xmax - 2)))
		return (0);
	if (consider_blizzards_down(map, x, y, steps % (map->ymax - 2)))
		return (0);
	if (consider_blizzards_up(map, x, y, steps % (map->ymax - 2)))
		return (0);
	return (1);
}
