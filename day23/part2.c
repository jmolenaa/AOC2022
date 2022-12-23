#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

t_adjacent	*make_new_adjacent_elf(int x, int y)
{
	t_adjacent	*elf = malloc(sizeof(t_adjacent));
	elf->x = x;
	elf->y = y;
	elf->next = NULL;
	return (elf);
}

void	put_in_list(t_adjacent **adjacent_elves, t_adjacent *new_elf)
{
	new_elf->next = *adjacent_elves;
	*adjacent_elves = new_elf;
}

void	get_adjacent(t_elf *elves, t_elf *current_elf, t_adjacent **adjacent_elves)
{
	t_adjacent	*new_adjacent_elf = NULL;

	for (t_elf *temp = elves; temp != NULL; temp = temp->next_elf)
	{
		if (temp == current_elf)
			continue ;
		if (	abs(current_elf->x_coordinate - temp->x_coordinate) <= 1\
			 && abs(current_elf->y_coordinate - temp->y_coordinate) <= 1)
		{
			new_adjacent_elf = make_new_adjacent_elf(temp->x_coordinate, temp->y_coordinate);
			put_in_list(adjacent_elves, new_adjacent_elf);
		}
	}
}

void	free_adjacent(t_adjacent **adjacent_elves)
{
	t_adjacent	*temp;
	
	while (*adjacent_elves != NULL)
	{
		temp = *adjacent_elves;
		*adjacent_elves = (*adjacent_elves)->next;
		free(temp);
	}
}

int	check_north(t_elf *current_elf, t_adjacent *adjacent_elves)
{
	for (t_adjacent *temp = adjacent_elves; temp != NULL; temp = temp->next)
	{
		if (temp->y - current_elf->y_coordinate == -1)
			return (0);
	}
	current_elf->x_proposed = current_elf->x_coordinate;
	current_elf->y_proposed = current_elf->y_coordinate - 1;
	return (1);
}

int	check_south(t_elf *current_elf, t_adjacent *adjacent_elves)
{
	for (t_adjacent *temp = adjacent_elves; temp != NULL; temp = temp->next)
	{
		if (temp->y - current_elf->y_coordinate == 1)
			return (0);
	}
	current_elf->x_proposed = current_elf->x_coordinate;
	current_elf->y_proposed = current_elf->y_coordinate + 1;
	return (1);
}

int	check_west(t_elf *current_elf, t_adjacent *adjacent_elves)
{
	for (t_adjacent *temp = adjacent_elves; temp != NULL; temp = temp->next)
	{
		if (temp->x - current_elf->x_coordinate == -1)
			return (0);
	}
	current_elf->x_proposed = current_elf->x_coordinate - 1;
	current_elf->y_proposed = current_elf->y_coordinate;
	return (1);
}

int	check_east(t_elf *current_elf, t_adjacent *adjacent_elves)
{
	for (t_adjacent *temp = adjacent_elves; temp != NULL; temp = temp->next)
	{
		if (temp->x - current_elf->x_coordinate == 1)
			return (0);
	}
	current_elf->x_proposed = current_elf->x_coordinate + 1;
	current_elf->y_proposed = current_elf->y_coordinate;
	return (1);
}

void	choose_direction(t_elf *elves, t_elf *current_elf, t_adjacent *adjacent_elves, int direction)
{
	if (adjacent_elves == NULL)
	{
		current_elf->not_adjacent = 1;
		current_elf->x_proposed = current_elf->x_coordinate;
		current_elf->y_proposed = current_elf->y_coordinate;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		current_elf->not_adjacent = 0;
		if (direction == 0 && check_north(current_elf, adjacent_elves))
			break ;
		if (direction == 1 && check_south(current_elf, adjacent_elves))
			break ;
		if (direction == 2 && check_west(current_elf, adjacent_elves))
			break ;
		if (direction == 3 && check_east(current_elf, adjacent_elves))
			break ;
		direction = (direction + 1) % 4;
		if (i == 3)
		{
			current_elf->x_proposed = current_elf->x_coordinate;
			current_elf->y_proposed = current_elf->y_coordinate;
		}
	}
}

void	propose_direction(t_elf *elves, int direction)
{
	t_adjacent	*adjacent_elves = NULL;

	for(t_elf *current_elf = elves; current_elf != NULL; current_elf = current_elf->next_elf)
	{
		get_adjacent(elves, current_elf, &adjacent_elves);
		choose_direction(elves, current_elf, adjacent_elves, direction);
		free_adjacent(&adjacent_elves);
	}
}

void	check_for_overlap(t_elf *elves)
{
	for (t_elf *current_elf = elves; current_elf != NULL; current_elf = current_elf->next_elf)
	{
		if (current_elf->x_proposed == current_elf->x_coordinate && current_elf->y_proposed == current_elf->y_coordinate)
			continue ;
		for (t_elf *temp = elves; temp != NULL; temp = temp->next_elf)
		{
			if (current_elf == temp)
				continue ;
			if (current_elf->x_proposed == temp->x_proposed && current_elf->y_proposed == temp->y_proposed)
			{
				current_elf->x_proposed = current_elf->x_coordinate;
				current_elf->y_proposed = current_elf->y_coordinate;
				temp->x_proposed = temp->x_coordinate;
				temp->y_proposed = temp->y_coordinate;
			}
		}
	}
}

void	move(t_elf *elves)
{
	while (elves != NULL)
	{
		elves->x_coordinate = elves->x_proposed;
		elves->y_coordinate = elves->y_proposed;
		elves = elves->next_elf;
	}
}

int	check_adjacency(t_elf *elves)
{
	while (elves != NULL)
	{
		if (elves->not_adjacent == 0)
			return (0);
		elves = elves->next_elf;
	}
	return (1);
}

void	get_moving(t_elf *elves)
{
	t_elf	*elftemp;

	for (int i = 0; 1; i++)
	{
		propose_direction(elves, i % 4);
		check_for_overlap(elves);
		move(elves);
		if (check_adjacency(elves))
		{
			printf("%d\n", i + 1);
			break ;
		}
	}
}

int	main()
{
	t_elf	*elves;
	int	fd = open("input", O_RDONLY);
	elves = get_elves(fd);
	get_moving(elves);
}