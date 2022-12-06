/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 13:18:19 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/20 15:05:56 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	e;

	if (*(needle) == '\0')
		return ((char *)haystack);
	i = 0;
	while (i < len)
	{
		if (*(haystack + i) == '\0')
			break ;
		e = 0;
		while (*(haystack + i + e) == *(needle + e))
		{
			if (i + e == len)
				break ;
			if (*(needle + e + 1) == '\0')
				return ((char *)haystack + i);
			e++;
		}
		i++;
	}
	return (NULL);
}
