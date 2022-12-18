#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_grid
{
	char	***grid;
	int		xmax;
	int		ymax;
	int		zmax;
}			t_grid;

typedef	struct s_pocket
{
	int				x;
	int				y;
	int				z;
	struct s_pocket	*nextloc;
}					t_pocket;

t_grid	*get_grid(void);
void	printgrid(t_grid *grid);

#endif