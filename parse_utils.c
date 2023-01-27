/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:14:34 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/28 00:09:35 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*rm_sp(char *str, char *new_str, size_t i);

char	*remove_spaces(char *str)
{
	size_t		i;
	char		*new_str;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] == 32)
		i++;
	new_str = ft_calloc(ft_strlen(str + i) + 1, sizeof(char *));
	if (!new_str)
		return (NULL);
	new_str = rm_sp(str, new_str, i);
	return (new_str);
}

static char	*rm_sp(char *str, char *new_str, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			k = ft_charcmp(str + i + 1, str[i]) + i + 1;
			while (i <= k)
				new_str[j++] = str[i++];
		}
		else if (str[i] == 32 && str[i + 1] == 32)
		{
			new_str[j] = str[i];
			i++;
			while (str[i] == 32)
				i++;
		}
		else if (str[i] && i == ft_strlen(str) && str[i] == 32)
			i++;
		else
			new_str[j++] = str[i++];
	}
	return (new_str);
}
