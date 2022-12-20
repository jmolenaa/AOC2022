#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	skip_to_next_number(char **str)
{
	while (ft_isdigit(**str) == 1)
		(*str)++;
	while (ft_isdigit(**str) == 0)
		(*str)++;
}

t_blueprint	*get_blueprint(int fd)
{
	char *str = get_next_line(fd);
	if (str == NULL)
		return (NULL);
	t_blueprint *blueprint = malloc(sizeof(t_blueprint));
	skip_to_next_number(&str);
	blueprint->id = ft_atoi(str);
	skip_to_next_number(&str);
	blueprint->cost_of_ore = ft_atoi(str);
	skip_to_next_number(&str);
	blueprint->cost_of_clay = ft_atoi(str);
	skip_to_next_number(&str);
	*blueprint->cost_of_obsidian = ft_atoi(str);
	skip_to_next_number(&str);
	*(blueprint->cost_of_obsidian + 1) = ft_atoi(str);
	skip_to_next_number(&str);
	*blueprint->cost_of_geode = ft_atoi(str);
	skip_to_next_number(&str);
	*(blueprint->cost_of_geode + 1) = ft_atoi(str);
	blueprint->amount_of_geodes = 0;
	return (blueprint);
}