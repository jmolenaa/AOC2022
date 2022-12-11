#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_item
{
	long long int	worrylevel;
	struct s_item	*nextitem;
}					t_item;

typedef struct s_monkey
{
	struct s_item	*itemlist;
	int				monkeynumber;
	char			operation;
	long long int	howmuch;
	long long int	test;
	int				monkeyfalse;
	int				monkeytrue;
	int				counter;
	struct s_monkey	*nextmonkey;
}					t_monkey;

t_monkey	*parseinput(void);
void		printitemlist(t_item *head);
void		print_monkeys(t_monkey *head);
void		add_back_item(t_item **lst, t_item *new);
void		print_monkey_items(t_monkey *head);

#endif