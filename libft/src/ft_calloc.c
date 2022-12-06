/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:51:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/17 10:55:19 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*str;
	size_t		i;

	i = 0;
	str = malloc(count * size);
	if (str == (NULL))
		return (NULL);
	while (i < count * size)
	{
		*((char *)str + i) = '\0';
		i++;
	}
	return (str);
}
