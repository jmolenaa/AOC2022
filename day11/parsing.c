#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "day11.h"

t_item	*make_new_item(char *str, int i)
{
	t_item *newitem;

	newitem = (t_item *)malloc(sizeof(t_item));
	newitem->worrylevel = ft_atoi(str + i + 1);
	newitem->nextitem = NULL;
	return (newitem);
}

void	add_back_monkey(t_monkey **lst, t_monkey *new)
{
	t_monkey	*temp;

	if (new != (NULL) && lst != (NULL))
	{
		if (*lst != (NULL))
		{
			temp = *lst;
			while (temp->nextmonkey != (NULL))
				temp = temp->nextmonkey;
			temp->nextmonkey = new;
		}
		else
			*lst = new;
	}
}

void	make_item_list(int fd, t_monkey *new_monkey)
{
	char	*str;
	t_item	*firstitem;
	t_item	*newitem;

	firstitem = (NULL);
	str = get_next_line(fd);
	for (int i = 0; *(str + i) != '\n'; i++)
	{
		if (*(str + i) == ',' || *(str + i) == ':')
		{
			newitem = make_new_item(str, i);
			add_back_item(&firstitem, newitem);
		}
	}
	new_monkey->itemlist = firstitem;
}

void	get_operation(int fd, t_monkey *new_monkey)
{
	char	*str;
	char	c;
	int		howmuch;

	str = get_next_line(fd);
	sscanf(str, " %*s %*s %*s %*s %c", &new_monkey->operation);
	sscanf(str, " %*s %*s %*s %*s %*c %c", &c);
	if (c == 'o')
		new_monkey->howmuch = -1;
	else
		sscanf(str, " %*s %*s %*s %*s %*c %lld", &new_monkey->howmuch);
}

t_monkey	*make_new_monkey(int fd)
{
	char		*str;
	t_monkey	*new_monkey;

	new_monkey = (t_monkey *)malloc(sizeof(t_monkey));
	sscanf(get_next_line(fd), "%*s %d", &new_monkey->monkeynumber);
	make_item_list(fd, new_monkey);
	get_operation(fd, new_monkey);
	sscanf(get_next_line(fd), " %*s %*s %*s %lld", &new_monkey->test);
	sscanf(get_next_line(fd), " %*s %*s %*s %*s %*s %d", &new_monkey->monkeytrue);
	sscanf(get_next_line(fd), " %*s %*s %*s %*s %*s %d", &new_monkey->monkeyfalse);
	new_monkey->nextmonkey = NULL;
	new_monkey->counter = 0;
	return (new_monkey);
}

t_monkey	*parseinput(void)
{
	t_monkey	*head;
	t_monkey	*newmonkey;
	int fd = open("input", O_RDONLY);

	head = NULL;
	while(1)
	{
		newmonkey = make_new_monkey(fd);
		add_back_monkey(&head, newmonkey);
		if (get_next_line(fd) == NULL)
			break ;
	}
	// print_monkeys(head);
	return (head);
}