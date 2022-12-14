/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:13:00 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 01:13:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n && *str1 && (*str1 == *str2))
	{
		n--;
		str1++;
		str2++;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
