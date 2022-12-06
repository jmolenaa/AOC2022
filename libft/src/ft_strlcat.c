/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:01:50 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/14 14:41:03 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	dstlen = ft_strlen(dst);
	i = 0;
	if (dstsize == 0 || dstlen >= dstsize)
		return (dstsize + ft_strlen(src));
	while (i < dstsize - dstlen - 1 && *(src + i) != '\0')
	{
		*(dst + dstlen + i) = *(src + i);
		i++;
	}
	*(dst + dstlen + i) = '\0';
	return (dstlen + ft_strlen(src));
}
