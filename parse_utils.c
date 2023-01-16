/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:14:34 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 14:28:13 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces(char *str)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		*new_str;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	while (str[i] && str[i] == 32)
		i++;	
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			k = ft_charcmp(str + i + 1, str[i]) + i + 1;
			while (i <= k)
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
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
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	return (new_str);
}
