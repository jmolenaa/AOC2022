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

char	*convert_to_base_five(long long int num)
{
	char	*str = ft_calloc(30, 1);
	char	digit;
	if (num > 0)
	{
		digit = num % 5 + 48;
		num = num /5;
		str = convert_to_base_five(num);
		for(int i = 0; 1; i++)
		{
			if (*(str + i) == '\0')
			{
				*(str + i) = digit;
				break ;
			}
		}
	}
	return (str);
}

char	convert(char c)
{
	if (c == '3')
		return ('=');
	if (c == '4')
		return ('-');
	if (c == '5')
		return ('0');
	return (c);
}

char	*decimal_to_SNAFU_converter(long long int num)
{
	char	*str = convert_to_base_five(num);
	int		strlen = ft_strlen(str);
	int		check;
	while (strlen > 0)
	{
		check = 0;
		if (*(str + strlen - 1) > '2')
		{
			*(str + strlen - 1) = convert(*(str + strlen - 1));
			*(str + strlen - 2) = *(str + strlen - 2) + 1;
			check = 1;
		}
		*(str + strlen) = *(str + strlen - 1);
		if (strlen == 1 && check == 1)
				*(str + strlen - 1) = '1';
		else if (strlen == 1)
			*(str + strlen - 1) = ' ';
		strlen--;
	}
	return (str);
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
	sum = get_sum();
	char *str = decimal_to_SNAFU_converter(sum);
	printf("%s\n", str);
}