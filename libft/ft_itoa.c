/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:54:28 by gskrasti          #+#    #+#             */
/*   Updated: 2021/12/20 00:54:28 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*ft_number(long nbr, int size);

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = n;
	size = 0;
	if (n <= 0)
	{
		size = 1;
		nbr *= (-1);
	}	
	while (n)
	{
		n /= 10;
		size++;
	}
	str = ft_number(nbr, size);
	return (str);
}

static char	*ft_number(long nbr, int size)
{
	char	*str;

	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	while (nbr > 0)
	{
		str[size] = nbr % 10 + '0';
		nbr /= 10;
		size--;
	}
	if (size == 0)
	{
		if (str[1] == '\0')
			str[0] = '0';
		else
			str[0] = '-';
	}
	return (str);
}
