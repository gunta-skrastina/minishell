/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:23:19 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 01:23:19 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t count)
{
	while (count && (*(unsigned char *)str1 == *(unsigned char *)str2))
	{
		count--;
		str1++;
		str2++;
	}
	if (count == 0)
		return (0);
	else
		return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
