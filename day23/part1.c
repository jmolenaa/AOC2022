#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	propose_direction(t_elf *elves)
{
	// t_elf	*current_elf;
	int	direction;

	for(t_elf *current_elf = elves; current_elf != NULL; current_elf = current_elf->next_elf)
	{
		
	}
}

void	get_moving(t_elf *elves)
{
	for (int i = 0; i < 10; i++)
	{
		propose_direction(elves);
	}
}

int	main()
{
	t_elf	*elves;
	int	fd = open("test", O_RDONLY);

	elves = get_elves(fd);
	get_moving(elves);
	// print_elves(elves);
}