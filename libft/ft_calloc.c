/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 02:07:46 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 02:07:46 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(num * size);
	if (!ptr)
		return (NULL);
	while (i < (num * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
