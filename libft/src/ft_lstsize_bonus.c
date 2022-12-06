/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:49:43 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/18 19:18:32 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst != (NULL))
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}
