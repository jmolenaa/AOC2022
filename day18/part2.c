#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

int	check_if_in_pocket(t_pocket **head, t_pocket *loc, t_grid *grid);

int	check_mah_sides(int x, int y, int z, t_grid *grid)
{
	int	exposedside = 0;

	if (*(*(*(grid->grid + z + 1) + y) + x) == '.')
		exposedside++;
	if (z == 0)
		exposedside++;
	else if (*(*(*(grid->grid + z - 1) + y) + x) == '.')
	{
		exposedside++;
	}
	if (*(*(*(grid->grid + z) + y + 1) + x) == '.')
		exposedside++;
	if (y == 0)
		exposedside++;
	else if (*(*(*(grid->grid + z) + y - 1) + x) == '.')
		exposedside++;
	if (*(*(*(grid->grid + z) + y) + x + 1) == '.')
		exposedside++;
	if (x == 0)
		exposedside++;
	else if (*(*(*(grid->grid + z) + y) + x - 1) == '.')
	{
		exposedside++;
	}
	return (exposedside);
}

int	get_surface(t_grid *grid)
{
	int	surface = 0;
	
	for (int z = 0; z <= grid->zmax; z++)
	{
		for (int y = 0; y <= grid->ymax; y++)
		{
			for (int x = 0; x <= grid->xmax; x++)
			{
				if (*(*(*(grid->grid + z) + y) + x) == '#')
					surface = surface + check_mah_sides(x, y, z, grid);
			}
		}
	}
	return (surface);
}

t_pocket	*make_new_location(int x, int y, int z)
{
	t_pocket	*new = malloc(sizeof(t_pocket));
	new->x = x;
	new->y = y;
	new->z = z;
	new->nextloc = NULL;
	return (new);
}

void	put_loc_front(t_pocket **head, t_pocket *new)
{
	new->nextloc = *head;
	*head = new;
}

int	check_if_in_list(int x, int y, int z, t_pocket *head)
{
	for (t_pocket *temp = head; temp != NULL; temp = temp->nextloc)
	{
		if (x == temp->x && y == temp->y && z == temp->z)
			return (1);
	}
	return (0);
}

int	check_if_valid_and_continue(int x, int y, int z, t_pocket **head, t_grid *grid)
{
	if (x == 0 || x == grid->xmax + 1 || y == 0 || y == grid->ymax + 1 || z == 0 || z == grid->zmax + 1)
		return (1);
	if (check_if_in_list(x, y, z, *head))
		return (0);
	t_pocket *new = make_new_location(x, y, z);
	put_loc_front(head, new);
	if (check_if_in_pocket(head, new, grid))
		return (1);
	return (0);
}

int	check_if_in_pocket(t_pocket **head, t_pocket *loc, t_grid *grid)
{
	if (*(*(*(grid->grid + loc->z + 1) + loc->y) + loc->x) == '.')
	{
		if (check_if_valid_and_continue(loc->x, loc->y, loc->z + 1, head, grid))
			return (1);
	}
	if (*(*(*(grid->grid + loc->z - 1) + loc->y) + loc->x) == '.')
	{
		if (check_if_valid_and_continue(loc->x, loc->y, loc->z - 1, head, grid))
			return (1);
	}
	if (*(*(*(grid->grid + loc->z) + loc->y + 1) + loc->x) == '.')
	{
		if (check_if_valid_and_continue(loc->x, loc->y + 1, loc->z, head, grid))
			return (1);
	}
	if (*(*(*(grid->grid + loc->z) + loc->y - 1) + loc->x) == '.')
	{
		if (check_if_valid_and_continue(loc->x, loc->y - 1, loc->z, head, grid))
			return (1);
	}
	if (*(*(*(grid->grid + loc->z) + loc->y) + loc->x + 1) == '.')
	{
		if (check_if_valid_and_continue(loc->x + 1, loc->y, loc->z, head, grid))
			return (1);
	}
	if (*(*(*(grid->grid + loc->z) + loc->y) + loc->x - 1) == '.')
	{
		if (check_if_valid_and_continue(loc->x - 1, loc->y, loc->z, head, grid))
			return (1);
	}
	return (0);
}

void	fill_pocket(t_pocket *head, t_grid *grid)
{
	for (t_pocket *temp = head; temp != NULL; temp = temp->nextloc)
	{
		*(*(*(grid->grid + temp->z) + temp->y) + temp->x) = '@';
	}
}

void	free_locations(t_pocket *head)
{
	t_pocket	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->nextloc;
		free(temp);
	}
}

void	make_first_loc(int x, int y, int z, t_grid *grid)
{
	t_pocket	*head;
	
	if (x == 0 || x == grid->xmax + 1 || y == 0 || y == grid->ymax + 1 || z == 0 || z == grid->zmax + 1)
		return ;
	head = make_new_location(x, y, z);
	if (check_if_in_pocket(&head, head, grid) == 0)
		fill_pocket(head, grid);
	free_locations(head);
	return ;

}

void	fill_pockets(t_grid *grid)
{
	for (int z = 1; z <= grid->zmax; z++)
	{
		for (int y = 1; y <= grid->ymax; y++)
		{
			for (int x = 1; x <= grid->xmax; x++)
			{
				if (*(*(*(grid->grid + z) + y) + x) == '.')
					make_first_loc(x, y, z, grid);
			}
		}
	}
}

int	main()
{
	t_grid	*grid;
	int		surface;

	grid = get_grid();
	fill_pockets(grid);
	surface = get_surface(grid);
	printgrid(grid);
	printf("exposed surface : %d\n", surface);
}