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
	if (ft_isdigit(*(monkey_str + 6)))
		return (ft_atoi(monkey_str + 6));
	return (calculate_value(get_monkeys(find_monkey(fd, monkey_str + 6), fd),\
	 						get_monkeys(find_monkey(fd, monkey_str + 13), fd),\
							*(monkey_str + 11)));
}

int	main()
{
	int	fd = open("input", O_RDONLY);
	char *rootstr = find_monkey(fd, "root");
	long long int	value_of_root = get_monkeys(rootstr, fd);
	printf ("%lld\n", value_of_root);
}
