#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	get_grid(t_map *map, int fd)
{
	int		strlen;
	char	*str;
	map->grid = ft_calloc(map->maxy + 1, sizeof(char *));
	for (int i = 0; i < map->maxy; i++)
	{
		*(map->grid + i) = ft_calloc(map->maxx + 1, sizeof(char));
		ft_memset(*(map->grid + i), ' ', map->maxx);
		str = get_next_line(fd);
		strlen = ft_strlen(str);
		*(str + strlen - 1) = '\0';
		ft_strcpynonull(*(map->grid + i), str);
	}
}

void	get_maxpositions(t_map *map, int fd)
{
	int	strlen;
	for (char *str = get_next_line(fd); ft_isdigit(*str) == 0; str = get_next_line(fd))
	{
		map->maxy++;
		strlen = ft_strlen(str) - 1;
		if (strlen > map->maxx)
			map->maxx = strlen;
	}
	map->maxy = map->maxy - 1;
	lseek(fd, 0, SEEK_SET);
}

void	get_instructions(t_map *map, int fd)
{
	get_next_line(fd);
	char	*str = get_next_line(fd);
	map->instructions = ft_strdup(str);
}

void	get_start_position(t_map *map)
{
	map->positiony = 0;
	for (int x = 0; *(*(map->grid) + x) != '.'; x++)
	{
		map->positionx = x;
	}
	map->positionx++;
	map->previous_positionx = map->positionx;
	map->previous_positiony = map->positiony;
}

t_map	*get_map(void)
{
	int	fd = open("input", O_RDONLY);
	t_map	*map = malloc(sizeof(t_map));
	map->direction = 0;
	map->maxx = 0;
	map->maxy = 0;
	get_maxpositions(map, fd);
	get_grid(map, fd);
	get_instructions(map,fd);
	get_start_position(map);
	// ft_print_grid(map->grid);
	// printf("%d, %d\n", map->maxx, map->maxy);
	// printf("\n");
	// printf("%s\n", map->instructions);
	// printf("%d, %d\n", map->positionx, map->positiony);
	close(fd);
	return (map);
}

t_sides	*get_sides(t_map *map)
{
	t_sides *sides;
	if (map->maxy > map->maxx)
		sides = get_cube_y(map);
	// else
	// {
	// 	sides = get_top_x(map);
	// 	get_front_x(map, sides);
	// 	get_bottom_x(map, sides);
	// 	get_back_x(map, sides);
	// 	get_left_x(map, sides);
	// 	get_right_x(map,sides);
	// }
	
	return (sides);
}
