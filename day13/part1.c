#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

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
	printf("\n%s%s\n", *list1, *list2);
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

int	main()
{
	char	*input1;
	char	*input2;
	int		indicenbr = 1;
	int		sumofindice = 0;
	int		comparison = 0;
	int	fd = open("input", O_RDONLY);

	printf ("first input	");
	while (1)
	{
		input1 = get_next_line(fd);
		input2 = get_next_line(fd);
		printf("\n%s\n%s\n", input1, input2);
		comparison = compare_lists(&input1, &input2);
		printf("comparison : %d\n", comparison);
		if (comparison < 0)
			sumofindice = sumofindice + indicenbr;
		indicenbr++;
		if (get_next_line(fd) == NULL)
			break ;
		printf("\nnext input	%d", indicenbr);
	}
	printf("sum of indices : %d\n", sumofindice);
}