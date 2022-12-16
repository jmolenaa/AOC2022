#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	printvalve(t_valve *valve)
{
	printf("\nValve %s\nflow rate = %d\nneighbors : ", valve->valvename, valve->flowrate);
	ft_print_grid(valve->neigbors);
}

void	printvalves(t_valve *firstvalve)
{
	while (firstvalve != NULL)
	{
		printvalve(firstvalve);
		firstvalve = firstvalve->next;
	}
}

char	**get_neigbors(char *str)
{
	int		i = 0;
	int		n = 1;

	while (*(str + i) != '\0')
	{
		if (*(str + i) == ',')
			n++;
		i++;
	}
	char	**neighbors = ft_calloc(n + 1, sizeof(char *));
	i = i - 3;
	while (n > 0)
	{
		n--;
		*(neighbors + n) = ft_calloc(3, 1);
		ft_strlcpy(*(neighbors + n), (str + i), 3);
		i = i - 4;
	}
	return (neighbors);
}

t_valve	*make_new_valve(char *str)
{
	t_valve	*new_valve = malloc(sizeof(t_valve));
	new_valve->valvename = ft_calloc(3, 1);
	sscanf(str, "%*s %s %*s %*s rate=%d", new_valve->valvename, &new_valve->flowrate);
	new_valve->neigbors = get_neigbors(str);
	new_valve->next = NULL;
	return (new_valve);
}

t_valve	*get_next_valve(int fd)
{
	char	*str;
	t_valve	*new_valve;

	str = get_next_line(fd);
	if (str == NULL)
		return (NULL);
	new_valve = make_new_valve(str);
	return (new_valve);
}

void	add_front(t_valve **head, t_valve *new)
{
	new->next = *head;
	*head = new;
}

t_valve	*get_valve_list(void)
{
	t_valve	*first_valve = NULL;
	int fd = open("input", O_RDONLY);
	t_valve	*next_valve;

	while (1)
	{
		next_valve = get_next_valve(fd);
		if (next_valve == NULL)
			break ;
		add_front(&first_valve, next_valve);	
	}
	return (first_valve);
}