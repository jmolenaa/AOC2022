/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:34:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/14 10:24:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	while (i >= 0)
	{
		if (*(s + i) == (char) c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
