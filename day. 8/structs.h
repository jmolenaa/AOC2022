#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_grid
{
	char	**trees;
	int		rows;
	int		columns;
	int		visibletrees;
	int		scenic_score_left;
	int		scenic_score_right;
	int		scenic_score_up;
	int		scenic_score_down;
	int		highestscenicscore;
}			t_grid;

#endif