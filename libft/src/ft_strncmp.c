/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 10:53:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/14 11:05:19 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (diff == 0 && i < n)
	{
		if (*(s1 + i) == '\0' && *(s2 + i) == '\0')
			return (diff);
		diff = (unsigned char)*(s1 + i) - (unsigned char)*(s2 + i);
		i++;
	}
	return (diff);
}
