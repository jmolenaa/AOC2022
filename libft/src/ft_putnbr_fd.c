/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:10:24 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/10/20 19:10:15 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	writenbr(long int nbr, int fd, int digits)
{
	char	c;

	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * -1;
	}
	if (digits > 0)
	{
		c = nbr % 10 + '0';
		nbr = nbr / 10;
		digits--;
		writenbr(nbr, fd, digits);
		write(fd, &c, 1);
	}
}

static int	ft_countdigits(int n)
{
	int	digits;

	digits = 0;
	if (n / 10)
	{
		n = n / 10;
		digits = ft_countdigits(n);
	}
	digits++;
	return (digits);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	int			digits;

	if (fd >= 0)
	{
		nbr = n;
		digits = ft_countdigits(nbr);
		writenbr(nbr, fd, digits);
	}
}
