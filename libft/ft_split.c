/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:10:43 by gskrasti          #+#    #+#             */
/*   Updated: 2021/11/29 03:10:43 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int		num_of_strings(char const *s, char c);
char	*str(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**strings;

	if (!s)
		return (NULL);
	len = num_of_strings(s, c);
	strings = (char **)malloc((len + 1) * sizeof(char *));
	if (!strings)
	{
		free(strings);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		while (s[0] == c)
			s++;
		strings[i] = str(s, c);
		s = s + ft_strlen(strings[i]);
		i++;
	}
	strings[i] = 0;
	return (strings);
}

int	num_of_strings(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	*str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}
