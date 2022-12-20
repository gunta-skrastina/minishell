/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:17:42 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/20 16:24:22 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(char *str, int i)
{
	char	quote;

	while (str[++i])
	{
		if (ft_charcmp(str, '$') < 0)
			return (str);
		if (ft_charcmp(str, '$') < i)
			i = ft_charcmp(str, '$');
		if (str[i] == '$')
			str = replace_env(str, i, 0);
		else if ((str[i] == '\'' || str[i] == '"')
			&& ft_charcmp(str + i + 1, str[i]) >= 0)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$' && quote == '"')
					str = replace_env(str, i, quote);
				i++;
			}
		}
		str = replace(str, i);
	}
	return (str);
}

char	*replace_env(char *str, int i, char quote)
{
	int		j;
	char	*env;

	j = 0;
	i++;
	if (str[i] == ' ')
		return (str);
	env = ft_calloc(ft_strlen(str + i) + 1, sizeof(char *));
	if (ft_isdigit(str[i]))
	{
		while (ft_isdigit(str[i + j]))
		{
			env[j] = str[i + j];
			j++;
		}
		return (ft_new_str(str, --i, j, env));
	}
	while (str[i + j] && str[i + j] != '\0' && str[i + j] != ' '
		&& str[i + j] != quote && str[i + j] != '$')
	{
		if (((str[i + j] == '\'' || str[i + j] == '"')
				&& ft_charcmp(str + i + j, str[i + j]) >= 0))
			return (ft_new_str(str, --i, j, env));
		env[j] = str[i + j];
		j++;
	}
	return (ft_new_str(str, --i, j, env));
}

char	*ft_new_str(char *str, int i, int j, char *env)
{
	char	*temp_begin;
	char	*temp_end;
	char	*new_env;

	temp_begin = ft_calloc(i + 1, sizeof(char *));
	temp_end = ft_calloc(ft_strlen(str + j) + 1, sizeof(char *));
	ft_memcpy(temp_begin, str, i);
	ft_memcpy(temp_end, str + i + ft_strlen(env) + 1, ft_strlen(str + j));
	if (getenv(env))
	{
		new_env = ft_calloc(ft_strlen(getenv(env)) + 1, sizeof(char *));
		new_env = getenv(env);
	}
	else
		new_env = ft_calloc(1, sizeof(char *));
	free (str);
	str = ft_strjoin(temp_begin, new_env);
	str = ft_strjoin(str, temp_end);
	free(temp_begin);
	free(temp_end);
	// if (new_env)
	// 	free(new_env);
	free(env);
	printf("%s\n", new_env);
	return (str);
}
