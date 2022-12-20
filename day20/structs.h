#ifndef STRUCTS_H
#define	STRUCTS_H

typedef	struct s_numbers
{
	long long int		number;
	int					numberid;
	int					moved;
	struct s_numbers	*next;
}						t_numbers;

t_numbers	*get_list(int *list_length);
void		print_numbers(t_numbers *first_number);
void		print_numbers_reverse(t_numbers *first_number);

#endif