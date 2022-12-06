/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:01:38 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/20 18:03:39 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (s1 == (NULL) || set == (NULL))
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		j = 0;
	while (*(s1 + i) != '\0')
	{
		if (ft_strchr(set, *(s1 + i)) == (NULL))
			break ;
		i++;
	}
	while (j > 0)
	{
		if (ft_strrchr(set, *(s1 + j)) == (NULL))
			break ;
		j--;
	}
	s = ft_substr(s1, i, j - i + 1);
	return (s);
}
