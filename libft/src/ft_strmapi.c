/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 08:41:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/17 10:25:13 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	size_t	i;

	i = 0;
	if (s == (NULL))
		return (NULL);
	s1 = (char *)malloc(ft_strlen(s) + 1);
	if (s1 == (NULL))
		return (NULL);
	while (*(s + i) != '\0')
	{
		*(s1 + i) = f(i, *(s + i));
		i++;
	}
	*(s1 + i) = '\0';
	return (s1);
}
