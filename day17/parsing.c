#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	point_last_rock_to_first(t_rocks *firstrock)
{
	t_rocks	*temp;

	temp = firstrock;
	while (temp->nextrock != NULL)
		temp = temp->nextrock;
	temp->nextrock = firstrock;
}

char	**get_rock(int fd, int ymax, char *str)
{
	char	**rock = ft_calloc(ymax + 1, sizeof(char *));
	for (int i = 0; i < ymax; i++)
	{
		*(rock + i) = ft_calloc(ft_strlen(str), sizeof(char));
		ft_strlcpy(*(rock + i), str, ft_strlen(str));
		str = get_next_line(fd);
	}
	return (rock);
}

int	get_ymax(int fd)
{
	off_t	temp;
	char	*str;
	int		y = 1;

	temp = lseek(fd, 0, SEEK_CUR);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL || *str == '\n')
			break ;
		y++;
	}
	lseek(fd, temp, SEEK_SET);
	return (y);
}

t_rocks	*make_new_rock(int fd, int i)
{
	char	*str;
	off_t	temp;

	str = get_next_line(fd);
	if (str == NULL)
		return (NULL);
	t_rocks	*newrock = malloc(sizeof(t_rocks));
	newrock->rockid = i;
	newrock->ymax = get_ymax(fd);
	newrock->rock = get_rock(fd, newrock->ymax, str);
	newrock->nextrock = NULL;
	return(newrock);
}

void	add_rock_back(t_rocks **firstrock, t_rocks *rock)
{
	t_rocks	*temp;

	if (*firstrock != (NULL))
	{
		temp = *firstrock;
		while (temp->nextrock != (NULL))
			temp = temp->nextrock;
		temp->nextrock = rock;
	}
	else
		*firstrock = rock;
}

t_rocks	*get_rocks(void)
{
	t_rocks	*firstrock = NULL;
	t_rocks	*rock;
	int	fd = open("rocks", O_RDONLY);
	int	i = 1;
	while (1)
	{
		rock = make_new_rock(fd, i);
		if (rock == NULL)
			break ;
		i++;
		add_rock_back(&firstrock, rock);
	}
	point_last_rock_to_first(firstrock);
	close(fd);
	return (firstrock);
}

t_jet	*get_jet_pattern(void)
{
	int		fd = open("input", O_RDONLY);
	t_jet	*jet = malloc(sizeof(t_jet));
	char	*str = get_next_line(fd);
	jet->jetpattern = ft_strdup(str);
	jet->begin = jet->jetpattern;
	close(fd);
	return (jet);
}