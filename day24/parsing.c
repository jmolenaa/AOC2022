#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	get_y_max(t_map *map, int fd)
{
	map->ymax = 0;
	for (char *str = get_next_line(fd); str != NULL; str = get_next_line(fd))
		map->ymax++;
	lseek(fd, 0 , SEEK_SET);
}

void	get_grid(t_map *map, int fd)
{
	map->grid = ft_calloc(map->ymax + 1, sizeof(char *));
	for (int i = 0; i < map->ymax; i++)
		*(map->grid + i) = ft_strtrim(ft_strdup(get_next_line(fd)), "\n");
	close(fd);
}

void	get_expedition_and_end_positions(t_map *map)
{
	map->x_expedition = 1;
	map->y_expedition = 0;
	map->x_end = map->xmax - 2;
	map->y_end = map->ymax - 1;
}

t_map	*get_map(void)
{
	int	fd = open("test", O_RDONLY);
	t_map	*map = malloc(sizeof(t_map));
	get_y_max(map, fd);
	get_grid(map, fd);
	map->xmax = ft_strlen(*map->grid);
	get_expedition_and_end_positions(map);
	return (map);
}