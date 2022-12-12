#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "struct.h"

void	printgrid(char **elev)
{
	int	i = 0;
	
	while (*(elev + i) != NULL)
	{
		printf("%s\n", *(elev + i));
		i++;
	}
}

void	printposition(int position[2])
{
	printf("%d %d\n", *position, *(position + 1));
}

t_grid	make_grid(void)
{
	char	*str;
	t_grid	grid;
	int fd = open("test", O_RDONLY);
	int i = 0;

	grid.rows = 0;
	while (get_next_line(fd))
		grid.rows++;
	grid.elev = (char **)ft_calloc(grid.rows + 1, sizeof(char *));
	lseek(fd, 0 , SEEK_SET);
	while (i < grid.rows)
		*(grid.elev + i++) = ft_strtrim(get_next_line(fd), "\n");
	grid.collumns = ft_strlen(*grid.elev);
	return (grid);	
}

void	get_start_end(t_grid *grid)
{
	int	j = 0;
	int	i = 0;

	while (*(grid->elev + j) != NULL)
	{
		i = 0;
		while (*(*(grid->elev + j) + i) != '\0')
		{
			if (*(*(grid->elev + j) + i) == 'S')
			{
				*(grid->start) = j;
				*(grid->start + 1) = i;

			}
			else if (*(*(grid->elev + j) + i) == 'E')
			{
				*(grid->end) = j;
				*(grid->end + 1) = i;
			}
			i++;
		}
		j++;
	}
}

int	travel(t_grid grid, int j, int i, int steps, int *stepmin)
{
	if (j < grid.rows && grid.elev[j + 1][i] - grid.elev[j][i] <= 1)
	{
		steps++;
	}
}

int	main()
{
	t_grid	grid;
	int		stepmin = 2000000;
	grid = make_grid();
	get_start_end(&grid);
	travel
}