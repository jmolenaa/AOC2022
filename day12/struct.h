#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_grid
{
	char	**elev;
	int		rows;
	int		collumns;
	int		start[2];
	int		end[2];
}			t_grid;

#endif