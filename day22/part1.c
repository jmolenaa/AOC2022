#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

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

int	wrap_around_right(t_map *map)
{
	int	start_position = map->positionx;
	map->positionx = 0;
	while(*(*(map->grid + map->positiony) + map->positionx) == ' ')
		map->positionx++;
	if (*(*(map->grid + map->positiony) + map->positionx) == '#')
	{
		map->positionx = start_position;
		return (1);
	}
	return (0);
}

void	move_right(t_map *map)
{
	while (map->steps > 0 && *(*(map->grid + map->positiony) + map->positionx + 1) == '.')
	{
		map->positionx++;
		map->steps--;
	}
	if (map->steps == 0 || *(*(map->grid + map->positiony) + map->positionx + 1) == '#')
		return ;
	if (wrap_around_right(map))
		return ;
	map->steps--;
	move_right(map);
}

int	wrap_around_down(t_map *map)
{
	int	start_position = map->positiony;
	map->positiony = 0;
	while(*(*(map->grid + map->positiony) + map->positionx) == ' ')
		map->positiony++;
	if (*(*(map->grid + map->positiony) + map->positionx) == '#')
	{
		map->positiony = start_position;
		return (1);
	}
	return (0);
}

void	move_down(t_map *map)
{
	while (map->steps > 0 && map->positiony < map->maxy - 1 && *(*(map->grid + map->positiony + 1) + map->positionx) == '.')
	{
		map->positiony++;
		map->steps--;
	}
	if (map->steps == 0 || (map->positiony < map->maxy - 1 && *(*(map->grid + map->positiony + 1) + map->positionx) == '#'))
		return ;
	if(wrap_around_down(map))
		return ;
	map->steps--;
	move_down(map);
}

int	wrap_around_left(t_map *map)
{
	int	start_position = map->positionx;
	map->positionx = ft_strlen(*(map->grid + map->positiony)) - 1;
	// printf(" hi %c\n", *(*(map->grid + map->positiony) + map->positionx));
	// printf("%d\n", map->positiony);
	while(*(*(map->grid + map->positiony) + map->positionx) == ' ')
	{
		map->positionx--;
	}
	if (*(*(map->grid + map->positiony) + map->positionx) == '#')
	{
		map->positionx = start_position;
		return (1);
	}
	return (0);
}

void	move_left(t_map *map)
{
	while (map->steps > 0 && map->positionx > 0 && *(*(map->grid + map->positiony) + map->positionx - 1) == '.')
	{
		map->positionx--;
		map->steps--;
	}
	if (map->steps == 0 || (map->positionx > 0 && *(*(map->grid + map->positiony) + map->positionx - 1) == '#'))
		return ;
	if (wrap_around_left(map))
		return ;
	map->steps--;
	move_left(map);
}

int	wrap_around_up(t_map *map)
{
	int	start_position = map->positiony;
	map->positiony = map->maxy - 1;
	// printf(" hi %c\n", *(*(map->grid + map->positiony) + map->positionx));
	// printf("%d\n", map->positionx);
	while(*(*(map->grid + map->positiony) + map->positionx) == ' ')
		map->positiony--;
	if (*(*(map->grid + map->positiony) + map->positionx) == '#')
	{
		map->positiony = start_position;
		return (1);
	}
	return (0);
}

void	move_up(t_map *map)
{
	while (map->steps > 0 && map->positiony > 0 && *(*(map->grid + map->positiony - 1) + map->positionx) == '.')
	{
		map->positiony--;
		map->steps--;
	}
	if (map->steps == 0 || (map->positiony > 0 && *(*(map->grid + map->positiony - 1) + map->positionx) == '#'))
		return ;
	if(wrap_around_up(map))
	{
		return ;
	}
	map->steps--;
	move_up(map);
}

void	change_direction(t_map *map)
{
	while (ft_isdigit(*map->instructions) != 0)
		map->instructions++;
	// printf("%c\n", *map->instructions);
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

void	move(t_map *map)
{
	int	i = 1;
	while (*(map->instructions) != '\0')
	{
		// printf("move : %d\n", i);
		map->steps = ft_atoi(map->instructions);
		// printf("%d\n", map->direction);
		// printf("%d\n", map->steps);
		if (map->direction == 0)
			move_right(map);
		if (map->direction == 1)
			move_down(map);
		if (map->direction == 2)
			move_left(map);
		if (map->direction == 3)
			move_up(map);
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

	map = get_map();
	move(map);
	get_password(map);
}
