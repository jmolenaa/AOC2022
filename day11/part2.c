#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "day11.h"

void	changeworry(t_monkey *currentmonkey)
{
	long long int	new_worry = currentmonkey->itemlist->worrylevel;
	if (currentmonkey->operation == '+')
	{
		if (currentmonkey->howmuch == -1)
			new_worry = new_worry + new_worry;
		else
			new_worry = new_worry + currentmonkey->howmuch;
	}
	else
	{
		if (currentmonkey->howmuch == -1)
			new_worry = new_worry * new_worry;
		else
			new_worry = new_worry * currentmonkey->howmuch;
	}
	currentmonkey->itemlist->worrylevel = new_worry;
}

int	check_condition(t_monkey *currentmonkey)
{
	long long int	temp;

	temp = currentmonkey->itemlist->worrylevel / currentmonkey->test;
	temp = temp * currentmonkey->test;
	if (temp == currentmonkey->itemlist->worrylevel)
	{
		currentmonkey->itemlist->worrylevel = currentmonkey->itemlist->worrylevel / currentmonkey->test;
		return (1);
	}
	else
		return (0);
}

t_item	*grab_item_list(t_monkey *firstmonkey, int monkey)
{
	while (firstmonkey != NULL)
	{
		if (firstmonkey->monkeynumber == monkey)
			return (firstmonkey->itemlist);
		firstmonkey = firstmonkey->nextmonkey;
	}
	return (NULL);
}

t_item	*throw_to_monkey(t_monkey *currentmonkey, int monkey, t_monkey *firstmonkey)
{	
	t_item	*nextitem = currentmonkey->itemlist->nextitem;
	while (firstmonkey != NULL)
	{
		if (firstmonkey->monkeynumber == monkey)
			break ;
		firstmonkey = firstmonkey->nextmonkey;
	}
	currentmonkey->itemlist->nextitem = NULL;
	add_back_item(&firstmonkey->itemlist, currentmonkey->itemlist);
	return (nextitem);
}

void	throw_items(t_monkey *currentmonkey, t_monkey *firstmonkey)
{
	int	newworry;

	while (currentmonkey->itemlist != NULL)
	{
		changeworry(currentmonkey);
		// printf("%d\n", currentmonkey->itemlist->worrylevel);
		// printf("%d\n", check_condition(currentmonkey));
		if (check_condition(currentmonkey))
			currentmonkey->itemlist = throw_to_monkey(currentmonkey, currentmonkey->monkeytrue, firstmonkey);
		else
			currentmonkey->itemlist = throw_to_monkey(currentmonkey, currentmonkey->monkeyfalse, firstmonkey);
		currentmonkey->counter++;
	}
}

void	start_throwing(t_monkey *firstmonkey)
{
	t_monkey	*currentmonkey;

	for (int i = 1; i < 10000; i++)
	{
		currentmonkey = firstmonkey;
		while (currentmonkey != NULL)
		{
			throw_items(currentmonkey, firstmonkey);
			currentmonkey = currentmonkey->nextmonkey;
		}
		// printf("%d :\n", i);
		// print_monkey_items(firstmonkey);
	}
}

void	get_count(t_monkey *firstmonkey)
{
	int	max1 = 0;
	int	max2 = 0;

	while (firstmonkey != NULL)
	{
		if (firstmonkey->counter > max1)
		{
			max2 = max1;
			max1 = firstmonkey->counter;
		}
		else if(firstmonkey->counter > max2)
			max2 = firstmonkey->counter;
		firstmonkey = firstmonkey->nextmonkey;
	}
	// printf("%d, %d\n", max1, max2);
	printf("%d\n", max1 * max2);
}


int	main()
{
	t_monkey	*firstmonkey;
	firstmonkey = parseinput();
	start_throwing(firstmonkey);
	get_count(firstmonkey);
	print_monkeys(firstmonkey);
}