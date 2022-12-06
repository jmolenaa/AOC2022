/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 10:34:35 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/14 10:23:42 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char) c)
			return ((char *) s + i);
		i++;
	}
	if ((char) c == '\0')
		return ((char *) s + i);
	return (NULL);
}
