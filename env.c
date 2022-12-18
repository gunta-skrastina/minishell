/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:17:42 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/18 18:25:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(char *str, int i)
{
	char	quote;

	while (str[++i])
	{
		if (str[i] == '$')
			replace_env(str, i, 0);
		else if ((str[i] == '\'' || str[i] == '"') && ft_charcmp(str + i + 1, str[i]) >= 0)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$' && quote == '"')
					str = replace_env(str, i, quote);
				i++;
			}
		}
		replace(str, i);
	}
	return (str);
}

char	*replace_env(char *str, int i, char quote)
{
	int		j;

	if (!env_exists(str))
	{
		j = i + 1;
		str[i] = '\0';
		if (quote == '"')
			while (str[j] && str[j] != quote && str[j] != ' ')
				j++;
		else
		{
			while (str[j])
			{
				if (((str[j] == '\'' || str[j] == '"')
					&& ft_charcmp(str + j + 1, str[j]) >= 0) || str[j] == ' ')
				{
					ft_strlcat(str, str + j, ft_strlen(str) + ft_strlen(str + j) + 1);
					return (str);
				}
				j++;
			}
		}
	}
	else
	{
		j = 0;
	}
	ft_strlcat(str, str + j, ft_strlen(str) + ft_strlen(str + j) + 1);
	return (str);
}

char	*env_exists(char *str)
{
	if (str)
		return (NULL);
	return (NULL);
}
