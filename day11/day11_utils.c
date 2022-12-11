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
		printf(", %d", head->worrylevel);
		head = head->nextitem;
	}
	printf("\n");
}

void	print_monkeys(t_monkey *head)
{
	while(head != NULL)
	{
		printf("Monkey %d\n", head->monkeynumber);
		printf("Holds items : %d", head->itemlist->worrylevel);
		printitemlist(head->itemlist->nextitem);
		printf("Operation = old %c", head->operation);
		if (head->howmuch == -1)
			printf(" old\n");
		else
			printf(" %d\n", head->howmuch);
		printf("Test : %d\nIf true : to monkey %d\nIf false : to monkey %d\n\n", head->test, head->monkeytrue, head->monkeyfalse);
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