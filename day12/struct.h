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

typedef struct s_store
{
	int		y;
	int		x;
	int		steps;
	struct	s_store *next;
}			t_store;

#endif