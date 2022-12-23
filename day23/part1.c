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
		current_elf->x_proposed = current_elf->x_coordinate;
		current_elf->y_proposed = current_elf->y_coordinate;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
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

void	get_moving(t_elf *elves)
{
	for (int i = 0; i < 10; i++)
	{
		propose_direction(elves, i % 4);
		check_for_overlap(elves);
		move(elves);
	}
}

t_rectangle	set_rectangle(void)
{
	t_rectangle rectangle;
	rectangle.xmax = 0;
	rectangle.xmin = 0;
	rectangle.ymax = 0;
	rectangle.ymin = 0;
	rectangle.elfcount = 0;
	return (rectangle);
}

void	get_answer(t_elf *elves)
{
	t_rectangle rectangle = set_rectangle();

	while (elves != NULL)
	{
		if (rectangle.xmax < elves->x_coordinate)
			rectangle.xmax = elves->x_coordinate;
		if (rectangle.xmin > elves->x_coordinate)
			rectangle.xmin = elves->x_coordinate;
		if (rectangle.ymax < elves->y_coordinate)
			rectangle.ymax = elves->y_coordinate;
		if (rectangle.ymin > elves->y_coordinate)
			rectangle.ymin = elves->y_coordinate;
		rectangle.elfcount++;
		elves = elves->next_elf;
	}
	int	field = abs(rectangle.xmax - rectangle.xmin + 1) * abs(rectangle.ymax - rectangle.ymin + 1);
	printf("%d\n", field - rectangle.elfcount);
	printf("%d, %d, %d, %d, %d\n", rectangle.xmax, rectangle.xmin, rectangle.ymax, rectangle.ymin, rectangle.elfcount);
}

int	main()
{
	t_elf	*elves;
	int	fd = open("input", O_RDONLY);

	elves = get_elves(fd);
	get_moving(elves);
	// print_elves(elves);
	get_answer(elves);
}