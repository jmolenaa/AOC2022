#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "day11.h"

void	printitemlist(t_item *head)
{
	while (head != NULL)
	{
		printf("%lld, ", head->worrylevel);
		head = head->nextitem;
	}
	printf("\n");
}

void	print_monkeys(t_monkey *head)
{
	while(head != NULL)
	{
		printf("Monkey %d\n", head->monkeynumber);
		printf("Holds items : ");
		printitemlist(head->itemlist);
		printf("Operation = old %c", head->operation);
		if (head->howmuch == -1)
			printf(" old\n");
		else
			printf(" %lld\n", head->howmuch);
		printf("Test : %lld\nIf true : to monkey %d\nIf false : to monkey %d\n", head->test, head->monkeytrue, head->monkeyfalse);
		printf("Counter : %d\n\n", head->counter);
		head = head->nextmonkey;
	}
}

void	print_monkey_items(t_monkey *head)
{
	while(head != NULL)
	{
		printf("Monkey %d holds items : ", head->monkeynumber);
		printitemlist(head->itemlist);
		head = head->nextmonkey;
	}
}

void	add_back_item(t_item **lst, t_item *new)
{
	t_item	*temp;

	if (new != (NULL) && lst != (NULL))
	{
		if (*lst != (NULL))
		{
			temp = *lst;
			while (temp->nextitem != (NULL))
				temp = temp->nextitem;
			temp->nextitem = new;
		}
		else
			*lst = new;
	}
}