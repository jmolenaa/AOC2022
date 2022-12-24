#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	change_position(t_map *map, int steps, int *minsteps, t_location **locations);

void	consider_right(t_map *map, int steps, int *minsteps, t_location **locations)
{
	int	temp;
	if (*(*(map->grid + map->y_expedition) + map->x_expedition + 1) == '#')
		return ;
	if (look_if_empty(map ,map->x_expedition + 1, map->y_expedition, steps))
	{
		temp = map->x_expedition;
		map->x_expedition = map->x_expedition + 1;
		change_position(map, steps + 1, minsteps, locations);
		map->x_expedition = temp;
	}
	return ;
}

void	consider_left(t_map *map, int steps, int *minsteps, t_location **locations)
{
	int	temp;
	if (*(*(map->grid + map->y_expedition) + map->x_expedition - 1) == '#')
		return ;
	if (look_if_empty(map ,map->x_expedition - 1, map->y_expedition, steps))
	{
		temp = map->x_expedition;
		map->x_expedition = map->x_expedition - 1;
		change_position(map, steps + 1, minsteps, locations);
		map->x_expedition = temp;
	}
	return ;
}

void	consider_down(t_map *map, int steps, int *minsteps, t_location **locations)
{
	int	temp;
	if (map->y_expedition + 1 == map->ymax || \
		*(*(map->grid + map->y_expedition + 1) + map->x_expedition) == '#')
		return ;
	if (look_if_empty(map ,map->x_expedition, map->y_expedition + 1, steps))
	{
		temp = map->y_expedition;
		map->y_expedition = map->y_expedition + 1;
		change_position(map, steps + 1, minsteps, locations);
		map->y_expedition = temp;
	}
	return ;
}

void	consider_up(t_map *map, int steps, int *minsteps, t_location **locations)
{
	int	temp;
	if (map->y_expedition - 1 == -1 || \
		*(*(map->grid + map->y_expedition - 1) + map->x_expedition) == '#')
		return ;
	if (look_if_empty(map ,map->x_expedition, map->y_expedition - 1, steps))
	{
		temp = map->y_expedition;
		map->y_expedition = map->y_expedition - 1;
		change_position(map, steps + 1, minsteps, locations);
		map->y_expedition = temp;
	}
	return ;
}

void	consider_waiting(t_map *map, int steps, int *minsteps, t_location **locations)
{
	if (look_if_empty(map ,map->x_expedition, map->y_expedition, steps))
		change_position(map, steps + 1, minsteps, locations);
	return ;
}

void	move_or_wait(t_map *map, int steps, int *minsteps, t_location **locations)
{
	consider_down(map, steps, minsteps, locations);
	consider_right(map, steps, minsteps, locations);
	consider_left(map, steps, minsteps, locations);
	consider_up(map, steps, minsteps, locations);
	consider_waiting(map, steps, minsteps, locations);
}

t_location	*make_new_location(int x, int y, int steps)
{
	t_location *new = malloc(sizeof(t_location));
	new->x = x;
	new->y = y;
	new->steps = steps;
	new->next = NULL;
	return (new);
}

void	add_front(t_location **locations, t_location *new)
{
	new->next = *locations;
	*locations = new;
}

int	check_locations_and_add(t_map *map, int steps, t_location **locations)
{
	for (t_location *temp = *locations; temp != NULL; temp = temp->next)
	{
		if (temp->x == map->x_expedition && temp->y == map->y_expedition && temp->steps == steps)
				return (1);
	}
	t_location *new = make_new_location(map->x_expedition, map->y_expedition, steps);
	add_front(locations, new);
	return (0);
}

int	check_manhattan(t_map *map, int steps, int minsteps)
{
	if (abs(map->x_end - map->x_expedition) + abs(map->y_end - map->y_expedition) > abs(minsteps - steps))
		return (1);
	return (0);
}

void	change_position(t_map *map, int steps, int *minsteps, t_location **locations)
{
	if (check_locations_and_add(map, steps, locations) || check_manhattan(map, steps, *minsteps) || steps >= *minsteps)
		return ;
	if (map->x_expedition == map->x_end && map->y_expedition == map->y_end)
	{
		if (steps < *minsteps)
			*minsteps = steps - 1;
		return ;
	}
	move_or_wait(map, steps, minsteps, locations);
}

void	free_locations(t_location *locations)
{
	t_location	*temp;
	while (locations != NULL)
	{
		temp = locations;
		locations = locations->next;
		free(temp);
	}
}

void	set_end_to_start(t_map *map)
{
	map->x_expedition = map->x_end;
	map->y_expedition = map->y_end;
	map->x_end = 1;
	map->y_end = 0;
}

void	set_start_to_end(t_map *map)
{
	map->x_expedition = map->x_end;
	map->y_expedition = map->y_end;
	map->x_end = map->xmax - 2;
	map->y_end = map->ymax - 1;
}

void	move(t_map *map)
{
	int	minsteps;
	int	totalsteps = 0;
	t_location *locations = NULL;

	for (int i = 0; i < 3; i++)
	{
		minsteps = 1000;
		change_position(map, totalsteps, &minsteps, &locations);
		totalsteps = minsteps;
		free_locations(locations);
		locations = NULL;
		if (i == 0)
		{
			printf("begin to end : %d\n", totalsteps);
			set_end_to_start(map);
		}
		if (i == 1)
		{
			printf("end to begin : %d\n", totalsteps);
			set_start_to_end(map);
		}
	}
	printf("back again : %d\n", totalsteps);
}

int	main()
{
	t_map	*map;
	map = get_map();
	move(map);
}
