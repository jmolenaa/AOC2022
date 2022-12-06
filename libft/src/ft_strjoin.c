/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:07:51 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/28 12:08:53 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (s2 == (NULL))
		return (NULL);
	if (s1 == (NULL))
	{
		s3 = (char *)malloc(ft_strlen(s2) + 1);
		if (s3 == (NULL))
			return (NULL);
		ft_strlcpy(s3, s2, ft_strlen(s2) + 1);
		return (s3);
	}
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == (NULL))
		return (NULL);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (s3);
}
