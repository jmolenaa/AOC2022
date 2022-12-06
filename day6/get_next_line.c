/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:36:41 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/12/06 08:41:41 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

char	*createreturnstring(t_strlst *strlist)
{
	char	*retstr;
	int		totallen;
	int		i;
	t_strlst	*temp;

	totallen = 0;
	temp = strlist;
	while (temp != (NULL))
	{
		totallen = totallen + strlenornewline(temp->str, 0);
		temp = temp->next;
	}
	retstr = (char *)malloc((totallen + 1) * sizeof(char));
	if (retstr == (NULL))
		return (freeing(strlist, (NULL)), (NULL));
	*(retstr + totallen) = '\0';
	temp = strlist;
	while (temp != (NULL))
	{
		i = strlenornewline(temp->str, 0);
		totallen = totallen - stringcpy(retstr + totallen - i, temp->str, i);
		temp = temp->next;
	}
	freeing(strlist, (NULL));
	return (retstr);
}

t_strlst	*addnode(t_strlst *head, char *buff)
{
	t_strlst	*newnode;

	newnode = (t_strlst *)malloc(sizeof(t_strlst));
	if (newnode == (NULL))
	{
		freeing(head, NULL);
		return (NULL);
	}
	newnode->str = substr(buff, 0, 1, 0);
	if (newnode->str == (NULL))
	{
		freeing(head, NULL);
		free(newnode);
		return (NULL);
	}
	newnode->next = head;
	return (newnode);
}

t_strlst	*nextlinenobuffer(int fd, t_strlst *strlist, char **strtemp)
{
	int		i;
	int		check;
	char	buff[BUFFER_SIZE + 1];

	i = 1;
	while (i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (freeing(strlist, (NULL)));
		*(buff + i) = '\0';
		strlist = addnode(strlist, buff);
		if (strlist == (NULL))
			return (NULL);
		check = strlenornewline(buff, 1);
		if (check < i)
		{
			*strtemp = substr(buff, check + 1, 0, 0);
			if (*strtemp == (NULL))
				return (freeing(strlist, (NULL)));
			return (strlist);
		}
	}
	return (strlist);
}

t_strlst	*nextlinewithbuffer(char **strtemp, t_strlst *strlist)
{
	int	strtemplenornewline;

	strtemplenornewline = strlenornewline(*strtemp, 1);
	if (*(*strtemp + strtemplenornewline) == '\n')
	{
		strlist = addnode(strlist, *strtemp);
		if (strlist == (NULL))
			return (freeing(NULL, strtemp));
		*strtemp = substr(*strtemp, strtemplenornewline + 1, 0, 1);
		if (*strtemp == (NULL))
			return (freeing(strlist, (NULL)));
		return (strlist);
	}
	strlist = addnode(strlist, *strtemp);
	freeing(NULL, strtemp);
	return (strlist);
}

char	*get_next_line(int fd)
{
	t_strlst		*strlist;
	char		*retstr;
	static char	*strtemp;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	strlist = (NULL);
	if (strtemp != (NULL))
	{
		strlist = nextlinewithbuffer(&strtemp, strlist);
		if (strtemp == (NULL) && strlist != (NULL))
			strlist = nextlinenobuffer(fd, strlist, &strtemp);
	}
	else
		strlist = nextlinenobuffer(fd, strlist, &strtemp);
	if (strlist == (NULL))
		return (NULL);
	retstr = createreturnstring(strlist);
	if (retstr == (NULL))
		return (freeing((NULL), &strtemp), (NULL));
	if ((strtemp != (NULL) && *strtemp == '\0'))
		freeing(NULL, &strtemp);
	if (retstr != (NULL) && *retstr == '\0')
		return (free(retstr), (NULL));
	return (retstr);
}
