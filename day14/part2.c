#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

void	fall(t_grid grid, int *sandx, int *sandy)
{
	if (*(*(grid.cave + *sandy + 1) + *sandx) == '.')
		*sandy = *sandy + 1;
	else if (*(*(grid.cave + *sandy + 1) + *sandx - 1) == '.')
	{
		*sandy = *sandy + 1;
		*sandx = *sandx - 1;
	}
	else if (*(*(grid.cave + *sandy + 1) + *sandx + 1) == '.')
	{
		*sandy = *sandy + 1;
		*sandx = *sandx + 1;
	}
	else
		*(*(grid.cave + *sandy) + *sandx) = 'o';
}

void	put_in_sand(t_grid grid)
{
	int	sandx;
	int	sandy;
	int	sandunit = 0;

	while(1)
	{
		sandx = 500;
		sandy = 0;
		if (*(*(grid.cave + sandy) + sandx) == 'o')
		{
			ft_print_grid(grid.cave);
			printf("%d\n", sandunit);
			break ;
		}
		while (sandy < grid.maxy - 1)
		{
			fall(grid, &sandx, &sandy);
			if (*(*(grid.cave + sandy) + sandx) == 'o')
				break ;
		}
		// if (sandy == grid.maxy - 1)
		// {
		// 	ft_print_grid(grid.cave);
		// 	printf("%d\n", sandunit);
		// 	break ;
		// }
		sandunit++;
	}
}

int	main()
{
	t_grid  grid;
	grid = make_grid();
	ft_memset(*(grid.cave + grid.maxy - 1), '#', ft_strlen(*(grid.cave + grid.maxy - 1)));
	// ft_print_grid(grid.cave);
	put_in_sand(grid);
}
