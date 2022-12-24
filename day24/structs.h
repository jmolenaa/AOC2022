#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_map
{
	char	**grid;
	int		ymax;
	int		xmax;
	int		x_expedition;
	int		y_expedition;
	int		x_end;
	int		y_end;
}			t_map;

typedef	struct s_location
{
	int	x;
	int	y;
	int	steps;
	struct s_location	*next;
}		t_location;


t_map	*get_map(void);
int		look_if_empty(t_map *map, int x, int y, int steps);

#endif