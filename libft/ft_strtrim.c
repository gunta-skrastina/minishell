/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:11:09 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 03:11:09 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	str_start;
	size_t	str_end;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		str_start = 0;
		str_end = ft_strlen(s1);
		while (s1[str_start] && ft_strchr(set, s1[str_start]))
			str_start++;
		while (s1[str_end - 1] && ft_strchr(set, s1[str_end - 1])
			&& str_end > str_start)
			str_end--;
		str = (char *) malloc(sizeof(char) * (str_end - str_start + 1));
		if (str)
			ft_strlcpy(str, &s1[str_start], str_end - str_start + 1);
	}
	return (str);
}
