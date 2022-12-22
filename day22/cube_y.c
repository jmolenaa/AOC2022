#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

t_sides	*get_top_y(t_map *map)
{
	t_sides	*top = malloc(sizeof(t_sides));
	top->ymin = 0;
	if (*(*(map->grid) + 50) == ' ')
		top->ymin = 50;
	top->name = ft_strdup("top");
	top->xmin = 50;
	top->xmax = top->xmin + 49;
	top->ymax = top->ymin + 49;
	top->next = NULL;
	// printf("%d, %d\n%d, %d\n", top->xmin, top->xmax, top->ymin, top->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + top->ymin) + top->xmin),  *(*(map->grid + top->ymin) + top->xmax),\
	// 							 *(*(map->grid + top->ymax) + top->xmin), *(*(map->grid + top->ymax) + top->xmax));
	return (top);
}

t_sides *get_top(t_map *map)
{
	t_sides	*top = malloc(sizeof(t_sides));
	int		x = 0;
	for (int i = 0; *(*(map->grid) + i) == ' '; i++)
		x++;
	top->name = ft_strdup("top");
	top->xmin = x;
	top->xmax = x + 49;
	top->ymax = 49;
	top->ymin = 0;
	top->next = NULL;
	// printf("%d, %d\n%d, %d\n", top->xmin, top->xmax, top->ymin, top->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + top->ymin) + top->xmin),  *(*(map->grid + top->ymin) + top->xmax),\
	// 							 *(*(map->grid + top->ymax) + top->xmin), *(*(map->grid + top->ymax) + top->xmax));
	return (top);
}

void	get_front_y(t_map *map, t_sides *sides)
{
	t_sides	*front = malloc(sizeof(t_sides));
	front->name = ft_strdup("front");
	front->xmin = sides->xmin;
	front->xmax = sides->xmax;
	front->ymin = sides->ymin + 50;
	front->ymax = sides->ymax + 50;
	sides->next = front;
	front->next = NULL;
	// printf("%d, %d\n%d, %d\n", front->xmin, front->xmax, front->ymin, front->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + front->ymin) + front->xmin),  *(*(map->grid + front->ymin) + front->xmax),\
	// 							 *(*(map->grid + front->ymax) + front->xmin), *(*(map->grid + front->ymax) + front->xmax));
}

void	get_bottom_y(t_map *map, t_sides *sides)
{
	t_sides	*bottom = malloc(sizeof(t_sides));
	bottom->name = ft_strdup("bottom");
	bottom->xmin = sides->xmin;
	bottom->xmax = sides->xmax;
	bottom->ymin = sides->ymin + 100;
	bottom->ymax = sides->ymax + 100;
	sides->next->next = bottom;
	bottom->next = NULL;
	// printf("%d, %d\n%d, %d\n", bottom->xmin, bottom->xmax, bottom->ymin, bottom->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + bottom->ymin) + bottom->xmin),  *(*(map->grid + bottom->ymin) + bottom->xmax),\
	// 							 *(*(map->grid + bottom->ymax) + bottom->xmin), *(*(map->grid + bottom->ymax) + bottom->xmax));
}

void	get_back_y(t_map *map, t_sides *sides)
{
	t_sides	*back = malloc(sizeof(t_sides));
	if (sides->ymin == 0)
		back->ymin = 150;
	else
		back->ymin = 0;
	int		x = 0;
	for (int i = 0; *(*(map->grid + back->ymin) + i) == ' '; i++)
		x++;
	back->name = ft_strdup("back");
	back->xmin = x;
	back->xmax = back->xmin + 49;
	back->ymax = back->ymin + 49;
	sides->next->next->next = back;
	back->next = NULL;
	// printf("%d, %d\n%d, %d\n", back->xmin, back->xmax, back->ymin, back->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + back->ymin) + back->xmin),  *(*(map->grid + back->ymin) + back->xmax),\
	// 							 *(*(map->grid + back->ymax) + back->xmin), *(*(map->grid + back->ymax) + back->xmax));
}

void	get_left_y(t_map *map, t_sides *sides)
{
	t_sides	*left = malloc(sizeof(t_sides));
	int	x = 0;
	for (int i = 0; *(*(map->grid + i)) == ' '; i++)
		x++;
	if (x == sides->next->next->next->ymin)
		x = x + 50;
	left->name = ft_strdup("left");
	left->xmin = 0;
	left->xmax = left->xmin + 49;
	left->ymin = x;
	left->ymax = left->ymin + 49;
	sides->next->next->next->next = left;
	left->next = NULL;
	// printf("%d, %d\n%d, %d\n", left->xmin, left->xmax, left->ymin, left->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + left->ymin) + left->xmin),  *(*(map->grid + left->ymin) + left->xmax),\
	// 							 *(*(map->grid + left->ymax) + left->xmin), *(*(map->grid + left->ymax) + left->xmax));
}

void	get_right_y(t_map *map, t_sides *sides)
{
	t_sides	*right = malloc(sizeof(t_sides));
	int	x = 0;
	for (int i = 0; *(*(map->grid + i) + 100) == ' '; i++)
		x++;
	if (x == sides->next->next->next->ymin)
		x = x + 50;
	right->name = ft_strdup("right");
	right->xmin = 100;
	right->xmax = right->xmin + 49;
	right->ymin = x;
	right->ymax = right->ymin + 49;
	sides->next->next->next->next->next = right;
	right->next = NULL;
	// printf("%d, %d\n%d, %d\n", right->xmin, right->xmax, right->ymin, right->ymax);
	// printf("%c, %c\n%c, %c\n",	 *(*(map->grid + right->ymin) + right->xmin),  *(*(map->grid + right->ymin) + right->xmax),\
	// 							 *(*(map->grid + right->ymax) + right->xmin), *(*(map->grid + right->ymax) + right->xmax));
}

t_sides	*get_cube_y(t_map *map)
{
	t_sides	*sides;
	sides = get_top_y(map);
	get_front_y(map, sides);
	get_bottom_y(map, sides);
	get_back_y(map, sides);
	get_left_y(map, sides);
	get_right_y(map,sides);
	return (sides);
}
