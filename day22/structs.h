#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_map
{
	char	**grid;
	int		positionx;
	int		positiony;
	int		maxx;
	int		maxy;
	int		direction;
	char	*instructions;
	int		steps;
	int		previous_positionx;
	int		previous_positiony;
}			t_map;

typedef struct s_sides
{
	char	*name;
	int		ymin;
	int		ymax;
	int		xmin;
	int		xmax;
	struct s_sides *next;
}			t_sides;

t_map	*get_map(void);
t_sides	*get_sides(t_map *map);
t_sides	*get_cube_y(t_map *map);
t_sides	*get_cube_x(t_map *map);

#endif