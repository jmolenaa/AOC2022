#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_elf
{
	int				x_coordinate;
	int				y_coordinate;
	int				direction;
	int				x_proposed;
	int				y_proposed;
	struct s_elf	*next_elf;
}					t_elf;

typedef	struct s_adjacent
{
	int					x;
	int					y;
	struct s_adjacent	*next;
}						t_adjacent;


t_elf	*get_elves(int fd);
void	print_elves(t_elf *elves);

#endif