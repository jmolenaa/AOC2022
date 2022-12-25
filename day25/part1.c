#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

long long int	convert_character(char c)
{
	if (c == '=')
		return (-2);
	else if (c == '-')
		return (-1);
	else
		return (c - 48);
}

long long int	SNAFU_to_decimal_converter(char *str)
{
	long long int	number = 0;
	long long int	multiplier = 1;
	for (int lastdigit = ft_strlen(str) - 2; lastdigit >= 0; lastdigit--)
	{
		number = number + (convert_character(*(str + lastdigit)) * multiplier);
		multiplier = multiplier * 5;
	}
	return (number);
}

int	convert_digit(char digit, long long int *num)
{
	digit = *num % 5 + 48;
	*num = *num / 5;
	if (digit > '2')
	{
		if (digit == '3')
			digit = '=';
		else
			digit = '-';
		*num = *num + 1;
	}
	return (digit);
}

int	test(long long int num, char *str)
{
	char	digit;
	int	i = 0;
	if (num > 0)
	{
		digit = convert_digit(digit, &num);
		i = test(num, str);
		*(str + i) = digit;
		i++;
	}
	return (i);
}

long long int	get_sum(void)
{
	int	fd = open("input", O_RDONLY);
	long long int	sum = 0;
	long long int	number;
	for (char *str = get_next_line(fd); str != NULL; str = get_next_line(fd))
	{
		number = SNAFU_to_decimal_converter(str);
		sum = sum + number;
	}
	return (sum);
}

int	main()
{
	long long int	sum;
	char	*str = ft_calloc(30, 1);
	sum = get_sum();
	test(sum, str);
	printf("%s\n", str);
}