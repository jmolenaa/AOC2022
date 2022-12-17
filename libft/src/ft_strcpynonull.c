/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpynonull.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 15:28:26 by janmolenaar   #+#    #+#                 */
/*   Updated: 2022/12/17 15:31:49 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpynonull(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dst + i) = *(src + i);
		i++;
	}
	return (ft_strlen(src));
}
