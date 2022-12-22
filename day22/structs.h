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
}			t_map;

t_map	*get_map(void);

#endif