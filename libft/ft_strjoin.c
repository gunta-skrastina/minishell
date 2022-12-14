/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:11:27 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 03:11:27 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		len;
	char	*ptr;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2 + 1;
	ptr = (char *) malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len1 + 1);
	ft_strlcat(ptr, s2, len);
	return (ptr);
}
