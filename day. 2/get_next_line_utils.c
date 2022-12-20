/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 20:22:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/11/28 13:00:17 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_list	*freeing(t_list *strlist, char **strtemp)
{
	int		j;
	t_list	*temp;

	j = 0;
	while (strlist != (NULL))
	{
		temp = strlist;
		free(strlist->str);
		strlist = strlist->next;
		free(temp);
	}
	if (strtemp != (NULL) && *strtemp != (NULL))
	{
		free(*strtemp);
		*strtemp = (NULL);
	}
	return (NULL);
}

int	stringcpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src != (NULL) && i < size && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	return (i);
}

char	*substr(char *str, int start, int newlineornot, int freecheck)
{
	char	*substr;
	int		length;
	int		i;

	length = strlenornewline(str, newlineornot);
	if (*(str + length) == '\n')
		length++;
	substr = (char *)malloc((length + 1) * sizeof(char));
	if (substr == (NULL))
	{
		if (freecheck)
			free(str);
		return (NULL);
	}
	i = stringcpy(substr, str + start, length);
	*(substr + i) = '\0';
	if (freecheck)
		free(str);
	return (substr);
}

int	strlenornewline(char *str, int newlineorrnot)
{
	int	check;

	check = 0;
	while (*(str + check) != '\0')
	{
		if (*(str + check) == '\n' && newlineorrnot == 1)
			return (check);
		check++;
	}
	return (check);
}
