#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "structs.h"

void	print_numbers(t_numbers *first_number)
{
	printf("\nnumber %d :%lld\n", first_number->numberid, first_number->number);
	for (t_numbers *temp = first_number->next; temp != first_number; temp = temp->next)
		printf("number %d :%lld\n", temp->numberid,  temp->number);
}

t_numbers	*make_new_number(int fd, int numberid)
{
	t_numbers	*new = malloc(sizeof(t_numbers));
	char *str = get_next_line(fd);
	if (str == NULL)
		return NULL;
	new->number = ft_atoi(str);
	new->moved = 0;
	new->numberid = numberid;
	new->next = NULL;
	return (new);
}

t_numbers	*get_list(int *list_length)
{
	int	numberid = 1;
	t_numbers *first_number = NULL;
	int	fd = open("input", O_RDONLY);
	first_number = make_new_number(fd, numberid);
	t_numbers *temp = first_number;
	numberid++;
	for(t_numbers *new = make_new_number(fd, numberid); new != NULL; new = make_new_number(fd, numberid))
	{
		(*list_length)++;
		temp->next = new;
		temp = new;
		numberid++;
	}
	temp->next = first_number;
	return (first_number);
}
