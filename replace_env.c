/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:17:42 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/04 13:57:19 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*init_env_list(char **envp)
{
	t_env_list	*env_list;
	int			i;
	char		**var;		

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		var = ft_split(envp[i], '=');
		ft_env_lstadd_back(&env_list, ft_env_lstnew(var[0], var[1]));
		i++;
		if (var)
		{
			free(var);
			var = NULL;
		}
	}
	return (env_list);
}

char	*replace(char *str, int i, t_env_list *env_list)
{
	char	quote;

	while (str[++i])
	{
		if (ft_charcmp(str, '$') < 0)
			return (str);
		if (ft_charcmp(str, '$') < i)
			i = ft_charcmp(str, '$');
		if (str[i] == '$')
			str = replace_env(str, i, 0, env_list);
		else if ((str[i] == '\'' || str[i] == '"')
			&& ft_charcmp(str + i + 1, str[i]) >= 0)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$' && quote == '"')
					str = replace_env(str, i, quote, env_list);
				i++;
			}
		}
		str = replace(str, i, env_list);
	}
	return (str);
}

char	*replace_env(char *str, int i, char quote, t_env_list *env_list)
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
		return (ft_new_str(str, --i, j, env, env_list));
	}
	while (str[i + j] && str[i + j] != '\0' && str[i + j] != ' '
		&& str[i + j] != quote && str[i + j] != '$')
	{
		if (((str[i + j] == '\'' || str[i + j] == '"')
				&& ft_charcmp(str + i + j, str[i + j]) >= 0))
			return (ft_new_str(str, --i, j, env, env_list));
		env[j] = str[i + j];
		j++;
	}
	return (ft_new_str(str, --i, j, env, env_list));
}

char	*ft_new_str(char *str, int i, int j, char *env, t_env_list *env_list)
{
	char	*temp_begin;
	char	*temp_end;
	char	*new_env;

	temp_begin = ft_calloc(i + 1, sizeof(char *));
	temp_end = ft_calloc(ft_strlen(str + j) + 1, sizeof(char *));
	ft_memcpy(temp_begin, str, i);
	ft_memcpy(temp_end, str + i + ft_strlen(env) + 1, ft_strlen(str + j));
	if (ft_getenv(env, env_list))
	{
		new_env = ft_calloc(ft_strlen(ft_getenv(env, env_list)) + 1, sizeof(char *));
		new_env = ft_getenv(env, env_list);
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
	return (str);
}

char	*ft_getenv(char *env, t_env_list *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(env, env_list->env_name, ft_strlen(env))
			&& ft_strlen(env) == ft_strlen(env_list->env_name))
			return (env_list->env_value);
		env_list = env_list->next;
	}
	return (NULL);
}
