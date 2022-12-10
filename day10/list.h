#ifndef LISTS_H
# define LISTS_H

typedef struct s_reg
{
	int				register_value;
	struct s_reg	*next;
}					t_reg;

#endif