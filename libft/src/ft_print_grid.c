/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_grid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 10:28:52 by janmolenaar   #+#    #+#                 */
/*   Updated: 2022/12/14 11:10:16 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_print_grid(char **str)
{
	int	i;

	i = 0;
	while (*(str + i) != 0)
	{
		printf("%s\n", *(str + i));
		i++;
	}
}