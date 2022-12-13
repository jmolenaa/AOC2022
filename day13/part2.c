#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "list.h"

int	compare_lists(char **list1, char **list2);

int	compare_number_list(int nbr, char **list)
{
	int	comparison = 0;

	char *nbrstring = ft_itoa(nbr);
	char *newlist = ft_strjoin("[", nbrstring);
	newlist = ft_strjoin(newlist, "]");
	comparison = compare_lists(&newlist, list);
	return (comparison);
}

int	compare_list_number(char **list, int nbr)
{
	int	comparison = 0;

	char *nbrstring = ft_itoa(nbr);
	char *newlist = ft_strjoin("[", nbrstring);
	newlist = ft_strjoin(newlist, "]");
	comparison = compare_lists(list, &newlist);
	return (comparison);
}

int	compare_lists(char **list1, char **list2)
{
	int	comparison = 0;
	(*list1)++;
	(*list2)++;
	while (**list1 != ']' && **list2 != ']' && comparison == 0)
	{
		if (ft_isdigit(**list1) && ft_isdigit(**list2))
		{
			comparison = ft_atoi(*list1) - ft_atoi(*list2);
			if (ft_atoi(*list1) > 9)
				(*list1)++;
			if (ft_atoi(*list2) > 9)
				(*list2)++;
		}
		else if (**list1 == '[' && **list2 == '[')
			comparison = compare_lists(list1, list2);
		else if (**list1 == '[' && ft_isdigit(**list2))
		{
			comparison = compare_list_number(list1, ft_atoi(*list2));
			if (ft_atoi(*list2) > 9)
				(*list2)++;
		}
		else if (ft_isdigit(**list1) && **list2 == '[')
		{
			comparison = compare_number_list(ft_atoi(*list1), list2);
			if (ft_atoi(*list1) > 9)
				(*list1)++;
		}
		if (comparison != 0)
			break ;
		(*list1)++;
		(*list2)++;
	}
	if (**list1 == ']' && **list2 != ']' && comparison == 0)
		return (-1);
	else if (**list1 != ']' && **list2 == ']' && comparison == 0)
		return (1);
	return (comparison);


}

t_signal *make_new(char *packet)
{
	t_signal *new;

	new = malloc(sizeof(t_signal));
	new->packet = ft_strdup(packet);
	new->nextpacket = NULL;
	return (new);
}

void	put_in_front(t_signal **head, t_signal *new)
{
	new->nextpacket = *head;
	*head = new;
}

void	printlist(t_signal *head)
{
	while (head != NULL)
	{
		printf("%s", head->packet);
		head = head->nextpacket;
	}
}

t_signal	*grab_in_list(char *packet, t_signal *head)
{
	t_signal *temp;
	char	*temppacket;
	char	*temppacket2;
	
	temppacket = packet;
	while (head != NULL)
	{
		temppacket = packet;
		temppacket2 = head->packet;
	// printf("%s%s", temppacket, temppacket2);
		if (compare_lists(&temppacket2, &temppacket) > 0)
			break ;
		head = head->nextpacket;
	}
	// printlist(head);
	return (head);

}

void	put_in_between(t_signal *head, t_signal *temp, t_signal *new)
{
	while (head != NULL && head->nextpacket != temp)
		head = head->nextpacket;
	head->nextpacket = new;
	new->nextpacket = temp;
}

int	main()
{
	char	*packet;
	int		indicenbr = 1;
	int		multipleofindice = 0;
	int		comparison = 0;
	int	fd = open("input", O_RDONLY);
	t_signal *head;
	t_signal *temp;
	t_signal *new;

	head = NULL;
	packet = get_next_line(fd);
	new = make_new(packet);
	put_in_front(&head, new);
	while (1)
	{
		packet = get_next_line(fd);
		if (packet == NULL)
			break ;
		if (*packet == '\n')
			continue ;
		new = make_new(packet);
		temp = grab_in_list(packet, head);
		if (temp == head)
			put_in_front(&head, new);
		else
			put_in_between(head, temp, new);
	}
	temp = head;
	while (temp != NULL)
	{
		if(ft_strncmp("[[2]]", temp->packet, 5) == 0)
			multipleofindice = indicenbr;
		if(ft_strncmp("[[6]]", temp->packet, 5)== 0)
			multipleofindice = multipleofindice * indicenbr;
		temp = temp->nextpacket;
		indicenbr++;
	}
	printlist(head);
	printf("multiple of indices is : %d\n", multipleofindice);
}

// Add [[2]] and [[6]] to input file as a new pair