#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_elf
{
	int				x_coordinate;
	int				y_coordinate;
	int				direction;
	int				x_proposed;
	int				y_proposed;
	int				not_adjacent;
	struct s_elf	*next_elf;
}					t_elf;

typedef	struct s_adjacent
{
	int					x;
	int					y;
	struct s_adjacent	*next;
}						t_adjacent;

typedef struct s_rectangle
{
	int	xmax;
	int	xmin;
	int	ymax;
	int	ymin;
	int	elfcount;
}		t_rectangle;

t_elf	*get_elves(int fd);
void	print_elves(t_elf *elves);
void	print_adjacent(t_adjacent *adjacent_elves);
void	print_proposed(t_elf *elves);
void	print_grid_kinda(t_elf *elves, t_rectangle s_rectangle);

#endif