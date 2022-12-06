/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:55:39 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/18 20:17:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == (NULL))
		return (NULL);
	while (lst->next != (NULL))
	{
		lst = lst->next;
	}
	return (lst);
}
