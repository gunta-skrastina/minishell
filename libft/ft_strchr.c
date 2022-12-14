/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:03:54 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 01:03:54 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *str, int ch)
{
	while ((*str != '\0') && (*str != ch))
	{
		str++;
	}
	if (*str == ch)
		return ((char *)str);
	return (NULL);
}
