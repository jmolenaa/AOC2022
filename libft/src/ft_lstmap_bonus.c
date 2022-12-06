/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 19:32:40 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/20 16:07:01 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*recur(t_list *l, void *(*f)(void *), \
void (*d)(void *), t_list *n)
{
	t_list	*temp;
	t_list	*check;

	if (l->next != (NULL))
	{
		temp = (t_list *)malloc(sizeof(t_list));
		if (!temp)
			return (NULL);
		n->next = temp;
		n->content = f(l->content);
		l = l->next;
		check = recur(l, f, d, temp);
		if (!check)
		{
			d(n->content);
			free(temp);
			return (NULL);
		}
	}
	else
	{
		n->next = (NULL);
		n->content = f(l->content);
	}
	return (n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*check;

	if (lst)
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			return (NULL);
		check = recur(lst, f, del, new);
		if (!check)
		{
			free(new);
			return (NULL);
		}
		return (new);
	}
	return (NULL);
}
