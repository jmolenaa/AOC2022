#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	move(t_map *map)
{
	while (*(map->instructions) != '\0')
	{
		if (map->direction == 0)
			move_right(map);
		if (map->direction == 1)
			move_down(map);
		if (map->direction == 2)
			move_left(map);
		if (map->direction == 3)
			move_up(map);
		change_direction(map);
	}
}

int	main()
{
	t_map	*map;

	map = get_map();
	move(map);
}
