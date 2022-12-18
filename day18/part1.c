#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

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

int	main()
{
	t_grid	*grid;
	int		surface;

	grid = get_grid();
	surface = get_surface(grid);
	printgrid(grid);
	printf("exposed surface : %d\n", surface);
}