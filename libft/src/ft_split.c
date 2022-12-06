/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 11:31:13 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/20 18:49:32 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	wcount;
	size_t	lcount;

	i = 0;
	wcount = 0;
	if (*s == '\0')
		return (wcount);
	while (*(s + i) != '\0' && c != '\0')
	{
		lcount = 0;
		if (*(s + i) != c)
			lcount++;
		if (*(s + i + 1) == c && lcount == 1)
			wcount++;
		i++;
	}
	if (lcount == 1 || c == '\0')
		wcount++;
	return (wcount);
}

static size_t	freearray(char **ret, size_t j, const char *s, char c)
{
	if (*(ret + j) == (NULL) && j != countwords(s, c))
	{
		while (j > 0)
		{
			j--;
			free(*(ret + j));
		}
		free(ret);
		return (1);
	}
	return (0);
}

static char	**createarray(char **ret, char const *s, char c, size_t i)
{
	size_t	j;
	size_t	lcount;

	j = 0;
	lcount = 0;
	while (*(s + i) != '\0' && j < countwords(s, c))
	{
		if (*(s + i) != c)
			lcount++;
		if (*(s + i) == c && lcount != 0)
		{
			*(ret + j) = ft_substr(s, i - lcount, lcount);
			if (freearray(ret, j, s, c))
				return (NULL);
			lcount = 0;
			j++;
		}
		i++;
	}
	if (lcount != 0)
		*(ret + j) = ft_substr(s, i - lcount, lcount);
	if (freearray(ret, j, s, c) && lcount != 0)
		return (NULL);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	**check;
	size_t	i;

	i = 0;
	if (s == (NULL))
		return (NULL);
	ret = (char **)malloc((countwords(s, c) + 1) * sizeof(char *));
	if (ret == (NULL))
		return (NULL);
	check = createarray(ret, s, c, i);
	if (check == (NULL))
		return (NULL);
	*(ret + countwords(s, c)) = (NULL);
	return (ret);
}
