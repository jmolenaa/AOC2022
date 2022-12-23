#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	print_elves(t_elf *elves)
{
	while (elves != NULL)
	{
		printf("coordinates : %d, %d\n", elves->x_coordinate, elves->y_coordinate);
		elves = elves->next_elf;
	}
}

t_elf	*make_new_elf(int x, int y)
{
	t_elf	*elf = malloc(sizeof(t_elf));
	elf->x_coordinate = x;
	elf->y_coordinate = y;
	elf->direction = 0;
	elf->next_elf = NULL;
	return (elf);
}

void	add_elf_back(t_elf **elves, t_elf *new_elf)
{
	t_elf *temp;
	temp = *elves;
	if (*elves == NULL)
	{
		*elves = new_elf;
		return ;
	}
	while (temp->next_elf != NULL)
		temp = temp->next_elf;
	temp->next_elf = new_elf;
}

void	get_elves_in_line(char *str, int y, t_elf **elves)
{
	t_elf	*new_elf;
	for (int i = 0; *(str + i) != '\0'; i++)
	{
		if (*(str + i) == '#')
		{
			new_elf = make_new_elf(i, y);
			add_elf_back(elves, new_elf);
		}
	}
}

t_elf	*get_elves(int fd)
{
	t_elf *elves = NULL;
	int	y = 0;
	for (char *str = get_next_line(fd); str != NULL; str = get_next_line(fd))
	{
		get_elves_in_line(str, y, &elves);
		y++;
	}
	return (elves);
}
