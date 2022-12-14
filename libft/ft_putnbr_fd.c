/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:03:15 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 03:03:15 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	ft_putnbr(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((n * (-1)), fd);
	}
	else if (n >= 2000000000)
	{
		ft_putchar_fd('2', fd);
		ft_putnbr_fd((n % 1000000000), fd);
	}
	else if (n >= 1000000000)
	{
		ft_putchar_fd('1', fd);
		ft_putnbr_fd((n % 1000000000), fd);
	}
	else
		ft_putnbr(n, fd);
}

static void	ft_putnbr(int n, int fd)
{
	int	i;

	i = 100000000;
	while (n % i == n)
	{
		n = n % i;
		i /= 10;
	}
	while (i > 0)
	{
		ft_putchar_fd((n / i + '0'), fd);
		n = n % i;
		i /= 10;
	}
}
