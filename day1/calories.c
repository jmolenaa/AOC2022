/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calories.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 13:58:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/12/01 17:54:28 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main()
{
	int		fd;
	int		max1;
	int		max2;
	int		max3;
	int		number;
	char	*str;

	max1 = -1;
	max2 = -2;
	max3 = -2;
	fd = open("justtesting", O_RDONLY);
	while (1)
	{
		number = 0;
		while (1)
		{
			str = get_next_line(fd);
			// printf("%s\n", str);
			if (str == (NULL) || *str == '\n')
				break ;
			number = number + ft_atoi(str);
		}
		if (number > max1)
		{
			max3 = max2;
			max2 = max1;
			max1 = number;
		}
		else if (number > max2)
		{
			max3 = max2;
			max2 = number;
		}
		else if (number > max3)
			max3 = number;
		if (str == (NULL))
			break ;
	}
	printf("%d\n", max1 + max2 + max3);
}