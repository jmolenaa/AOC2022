#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "list.h"

void	printlist(t_reg *head)
{
	int	i = 1;

	while (head != (NULL))
	{
		printf("%d : %d\n", i, head->register_value);
		i++;
		head = head->next;
	}
}

t_reg	*addnew(int register_value)
{
	t_reg	*new;

	new = (t_reg *)malloc(sizeof(t_reg));
	if (new == (NULL))
		return (NULL);
	new->register_value = register_value;
	new->next = (NULL);
	return (new);
}

void	add_back(t_reg **lst, t_reg *new)
{
	t_reg	*temp;

	if (new != (NULL) && lst != (NULL))
	{
		if (*lst != (NULL))
		{
			temp = *lst;
			while (temp->next != (NULL))
				temp = temp->next;
			temp->next = new;
		}
		else
			*lst = new;
	}
}

t_reg	*make_list(int fd)
{
	char	*str;
	t_reg	*head;
	t_reg	*temp;
	t_reg	*new;
	int		register_value = 1;

	// register_value = (int *)malloc(4);
	// *register_value = 1;
	head = addnew(register_value);
	temp = head;
	// printf("%d\n", temp->register_value);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*str == 'n')
		{
			new = addnew(register_value);
			add_back(&temp, new);
			temp = new;
			continue ;
		}
		new = addnew(register_value);
		add_back(&temp, new);
		temp = new;
		register_value = register_value + ft_atoi(str + 4);
		new = addnew(register_value);
			// printf("%d\n", new->register_value);
		add_back(&temp, new);
		temp = new;
	}
	return (head);
}

void	count_relevant_registers(t_reg *head)
{
	int	count = 0;
	int	cycle = 1;

	for (int i = 0; i < 19; i++)
	{
		head = head->next;
		cycle++;
	}
	count = head->register_value * cycle;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 40; i++)
		{
			head = head->next;
			cycle++;
		}
		count = count + head->register_value * cycle;
	}
	printf("%d\n", count);
}

void	print_output(t_reg *head)
{
	int	cycle = 1;
	int	i = 0;

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 40; i++)
		{
			if (head == NULL)
				break ;
			if (i >= head->register_value - 1 && i <= head->register_value + 1)
				write(1, "#", 1);
			else
				write(1, ".", 1);
			head = head->next;
		}
		write(1, "\n", 1);
	}
}

int	main()
{
	t_reg	*head;
	int fd = open("input", O_RDONLY);

	head = make_list(fd);
	printlist(head);
	print_output(head);
}