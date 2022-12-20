#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	move_number(t_numbers **first_number, t_numbers *number_to_move, int how_many_moves)
{
	t_numbers	*temp;
	t_numbers	*number_before_moved;
	temp = number_to_move;
	for (int i = 0; i < how_many_moves; i++)
		temp = temp->next;
	for (number_before_moved = temp; number_before_moved->next != number_to_move; number_before_moved = number_before_moved->next)
	if (number_to_move == *first_number)
		*first_number = (*first_number)->next;
	number_before_moved->next = number_to_move->next;
	number_to_move->next = temp->next;
	temp->next = number_to_move;
}


void	move_next_number(t_numbers **first_number, int list_length)
{
	t_numbers	*number_to_move;
	number_to_move = *first_number;
	while (number_to_move->moved != 0)
		number_to_move = number_to_move->next;
	number_to_move->moved = 1;
	int	how_many_moves = number_to_move->number % (list_length - 1);
	if (how_many_moves < 0)
		how_many_moves = list_length - abs(how_many_moves) - 1;
	if (how_many_moves != 0)
		move_number(first_number, number_to_move, how_many_moves);
}

void	move_numbers(t_numbers *first_number, int list_length)
{
	for (int i = 0; i < list_length; i++)
		move_next_number(&first_number, list_length);
}

void	get_sum(t_numbers *first_number)
{
	int	sum = 0;
	while (first_number->number != 0)
		first_number = first_number->next;
	for (int i = 1; i < 3001; i++)
	{
		first_number = first_number->next;
		if (i == 1000 || i == 2000 || i == 3000)
			sum = sum + first_number->number;
	}
	printf("%d\n", sum);
}

int	main()
{
	t_numbers	*first_number;
	int			list_length = 1;

	first_number = get_list(&list_length);
	move_numbers(first_number, list_length);
	get_sum(first_number);
}
