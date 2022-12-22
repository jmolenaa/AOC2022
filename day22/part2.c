#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	move_direction(t_map *map, t_sides *sides);

void	print_sides(t_sides *sides)
{
	while (sides != NULL)
	{
		printf("%s\n%d, %d\n%d, %d\n", sides->name, sides->xmin, sides->xmax, sides->ymin, sides->ymax);
		sides = sides->next;
	}
}

void	print_position(t_map *map)
{
	*(*(map->grid + map->previous_positiony) + map->previous_positionx) = 'S';
	*(*(map->grid + map->positiony) + map->positionx) = 'P';
	ft_print_grid(map->grid);
	*(*(map->grid + map->positiony) + map->positionx) = '.';
	*(*(map->grid + map->previous_positiony) + map->previous_positionx) = '.';
	map->previous_positionx = map->positionx;
	map->previous_positiony = map->positiony;
	printf("\n");
}

t_sides	*get_side(t_map *map, t_sides *sides)
{
	t_sides	*side;
	side = sides;
	while (side != NULL)
	{
		if (map->positionx >= side->xmin && map->positionx <= side->xmax && map->positiony >= side->ymin && map->positiony <= side->ymax)
			break;
		side = side->next;
	}
	return (side);
}

void	wrap_top(t_map *map)
{
	if (map->direction == 2)
	{
		map->direction = 0;
		map->positionx = 0;
		map->positiony = 149 - map->positiony;
	}
	if (map->direction == 3)
	{
		map->direction = 0;
		map->positiony = 150 + map->positionx - 50;
		map->positionx = 0;
	}
}

void	wrap_front(t_map *map)
{
	if (map->direction == 2)
	{
		map->direction = 1;
		map->positionx = map->positiony - 50;
		map->positiony = 100;
	}
	if (map->direction == 0)
	{
		map->direction = 3;
		map->positionx = 100 + map->positiony - 50;
		map->positiony = 49;
	}
}

void	wrap_bottom(t_map *map)
{
	if (map->direction == 0)
	{
		map->direction = 2;
		map->positiony = 149 - map->positiony;
		map->positionx = 149;
	}
	if (map->direction == 1)
	{
		map->direction = 2;
		map->positiony = 150 + map->positionx - 50;
		map->positionx = 49;
	}
}

void	wrap_back(t_map *map)
{
	if (map->direction == 0)
	{
		map->direction = 3;
		map->positionx = 50 + map->positiony - 150;
		map->positiony = 149;
	}
	if (map->direction == 1)
	{
		map->positionx = 100 + map->positionx;
		map->positiony = 0;
	}
	if (map->direction == 2)
	{
		map->direction = 1;
		map->positionx = 50 + map->positiony - 150;
		map->positiony = 0;
	}
}

void	wrap_right(t_map *map)
{
	if (map->direction == 0)
	{
		map->direction = 2;
		map->positiony = 149 - map->positiony;
		map->positionx = 99;
	}
	if (map->direction == 1)
	{
		map->direction = 2;
		map->positiony = 50 + map->positionx - 100;
		map->positionx = 99;
	}
	if (map->direction == 3)
	{
		map->positionx = map->positionx - 100;
		map->positiony = 199;
	}
}

void	wrap_left(t_map *map)
{
	if (map->direction == 2)
	{
		map->direction = 0;
		map->positionx = 50;
		map->positiony = 149 - map->positiony;
	}
	if (map->direction == 3)
	{
		map->direction = 0;
		map->positiony = 50 + map->positionx;
		map->positionx = 50;
	}
}

void	wrap_side(char *side_name, t_map *map)
{
	if (ft_strncmp(side_name, "top", 3) == 0)
		wrap_top(map);
	else if (ft_strncmp(side_name, "front", 5) == 0)
		wrap_front(map);
	else if (ft_strncmp(side_name, "bottom", 6) == 0)
		wrap_bottom(map);
	else if (ft_strncmp(side_name, "back", 4) == 0)
		wrap_back(map);
	else if (ft_strncmp(side_name, "right", 5) == 0)
		wrap_right(map);
	else if (ft_strncmp(side_name, "left", 4) == 0)
		wrap_left(map);
	map->steps--;
}

int	wrap(t_map *map, t_sides *sides)
{
	int	start_positionx = map->positionx;
	int	start_direction = map->direction;
	int	start_positiony = map->positiony;
	t_sides *side = get_side(map, sides);
	wrap_side(side->name, map);
	if (*(*(map->grid + map->positiony) + map->positionx) == '#')
	{
		map->positiony = start_positiony;
		map->direction = start_direction;
		map->positionx = start_positionx;
		return (1);
	}
	move_direction(map, sides);
	return (0);
}

void	move_right(t_map *map, t_sides *sides)
{
	while (map->steps > 0 && *(*(map->grid + map->positiony) + map->positionx + 1) == '.')
	{
		map->positionx++;
		map->steps--;
	}
	if (map->steps == 0 || *(*(map->grid + map->positiony) + map->positionx + 1) == '#')
		return ;
	if (wrap(map, sides))
		return ;
}

void	move_down(t_map *map, t_sides *sides)
{
	while (map->steps > 0 && map->positiony < map->maxy - 1 && *(*(map->grid + map->positiony + 1) + map->positionx) == '.')
	{
		map->positiony++;
		map->steps--;
	}
	if (map->steps == 0 || (map->positiony < map->maxy - 1 && *(*(map->grid + map->positiony + 1) + map->positionx) == '#'))
		return ;
	if(wrap(map, sides))
		return ;
}

void	move_left(t_map *map, t_sides *sides)
{
	while (map->steps > 0 && map->positionx > 0 && *(*(map->grid + map->positiony) + map->positionx - 1) == '.')
	{
		map->positionx--;
		map->steps--;
	}
	if (map->steps == 0 || (map->positionx > 0 && *(*(map->grid + map->positiony) + map->positionx - 1) == '#'))
		return ;
	if (wrap(map, sides))
		return ;
}

void	move_up(t_map *map, t_sides *sides)
{
	while (map->steps > 0 && map->positiony > 0 && *(*(map->grid + map->positiony - 1) + map->positionx) == '.')
	{
		map->positiony--;
		map->steps--;
	}
	if (map->steps == 0 || (map->positiony > 0 && *(*(map->grid + map->positiony - 1) + map->positionx) == '#'))
		return ;
	if(wrap(map, sides))
		return ;
}

void	change_direction(t_map *map)
{
	while (ft_isdigit(*map->instructions) != 0)
		map->instructions++;
	if (*map->instructions == '\0')
		return ;
	else if (*map->instructions == 'R')
	{
		map->direction++;
		if (map->direction == 4)
			map->direction = 0;
	}
	else
	{
		map->direction--;
		if (map->direction == -1)
			map->direction = 3;
	}
	map->instructions++;
}

void	move_direction(t_map *map, t_sides *sides)
{
	if (map->direction == 0)
		move_right(map, sides);
	else if (map->direction == 1)
		move_down(map, sides);
	else if (map->direction == 2)
		move_left(map, sides);
	else if (map->direction == 3)
		move_up(map, sides);
}

void	move(t_map *map, t_sides *sides)
{
	int	i = 1;
	while (*(map->instructions) != '\0')
	{
		// printf("%s\n", sides->name);
		// printf("move : %d\n", i);
		map->steps = ft_atoi(map->instructions);
		move_direction(map, sides);
		change_direction(map);
		// print_position(map);
		i++;
	}
}

void	get_password(t_map *map)
{
	int	password;
	printf("%d, %d, %d\n", map->positiony, map->positionx, map->direction);
	password = 1000 * (map->positiony + 1) + 4 * (map->positionx + 1) + map->direction;
	printf("%d\n", password);
}

int	main()
{
	t_map	*map;
	t_sides	*sides;

	map = get_map();
	sides = get_sides(map);
	move(map, sides);
	get_password(map);
}
