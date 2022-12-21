#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

char	*find_monkey(int fd, char *monkey)
{
	char	*monkey_str;
	lseek(fd, 0, SEEK_SET);
	for (monkey_str = get_next_line(fd); ft_strncmp(monkey_str, monkey, 4) != 0; monkey_str =get_next_line(fd))
	{}
	return (monkey_str);
}

long long int	calculate_value(long long int first, long long int second, char operator)
{
	if (operator == '*')
		return (first * second);
	else if (operator == '+')
		return (first + second);
	else if (operator == '-')
		return (first - second);	
	return (first / second);
}

long long int	get_monkeys(char *monkey_str, int fd)
{
	char	*first_monkey;
	char	*second_monkey;
	if (ft_strncmp(monkey_str, "humn", 4) == 0)
		return (-1);
	if (ft_isdigit(*(monkey_str + 6)))
		return (ft_atoi(monkey_str + 6));
	long long int value_first_monkey = get_monkeys(find_monkey(fd, monkey_str + 6), fd);
	long long int value_second_monkey = get_monkeys(find_monkey(fd, monkey_str + 13), fd);
	if (value_first_monkey == -1 || value_second_monkey == -1)
		return (-1);
	return (calculate_value(value_first_monkey, value_second_monkey, *(monkey_str + 11)));
}

char	*find_monkey_from_back(int fd, char *monkey)
{
	char	*monkey_str;
	lseek(fd, 0, SEEK_SET);
	for (monkey_str = get_next_line(fd); monkey_str != NULL; monkey_str =get_next_line(fd))
	{
		if (ft_strncmp(monkey, monkey_str + 6, 4) == 0)
			break ;
		if (ft_strncmp(monkey, monkey_str + 13, 4) == 0)
			break ;
	}
	if (monkey_str == (NULL))
		return(find_monkey(fd, monkey));
	return (monkey_str);
}

long long int calculate_value_from_back(long long int first, long long int second, char operator, int check)
{
	if (operator == '+')
		return (first - second);
	if (operator == '*')
		return (first / second);
	if (operator == '-')
	{
		if (check == 0)
			return (first + second);
		return (llabs(first - second));
	}
	if (check == 0)
		return (first * second);
	return (first / second);
}

long long int	get_value_from_back(int fd, char *monkeystr, long long int value_to_compare, char *monkey_to_compare, int check)
{
	char	*first_monkey;
	long long int	value_of_second_monkey;
	if (ft_strncmp(monkeystr, "root", 4) == 0)
		return (value_to_compare);
	first_monkey = find_monkey_from_back(fd, monkeystr);
	if (check == 0)
		value_of_second_monkey = get_monkeys(find_monkey(fd, monkeystr + 13), fd);
	else
		value_of_second_monkey = get_monkeys(find_monkey(fd, monkeystr + 6), fd);
	return (calculate_value_from_back(	get_value_from_back(fd, first_monkey, value_to_compare, monkey_to_compare, ft_strncmp(monkeystr, first_monkey + 6, 4))\
										, value_of_second_monkey, *(monkeystr + 11), check));
}

int	main()
{
	int	fd = open("test", O_RDONLY);
	char *rootstr = find_monkey(fd, "root");
	long long int value_human;
	long long int	value_of_first_monkey_of_root = get_monkeys(find_monkey(fd, rootstr + 6), fd);
	long long int	value_of_second_monkey_of_root = get_monkeys(find_monkey(fd, rootstr + 13), fd);
	char *humanstr = find_monkey_from_back(fd, "humn");
	if (value_of_first_monkey_of_root == -1)
		value_human = get_value_from_back(fd, humanstr, value_of_second_monkey_of_root, rootstr + 6, ft_strncmp(humanstr + 6, "humn", 4));
	else
		value_human = get_value_from_back(fd, humanstr, value_of_first_monkey_of_root, rootstr + 13, ft_strncmp(humanstr + 6, "humn", 4));
	printf("%lld\n", value_human);
}
