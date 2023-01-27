/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:17:42 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/27 20:11:26 by gskrasti         ###   ########.fr       */
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
		var = split_env(envp[i], '=');
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
		if (str[i] == '$' && str[i + 1] && str[i + 1] == 32)
			i++;
		if (ft_charcmp(str + i, '$') < 0)
			return (str);
		if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '\0')
			str = replace_env(str, i, env_list);
		else if ((str[i] == '\'' || str[i] == '"')
			&& ft_charcmp(str + i + 1, str[i]) >= 0)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote && str[i + 1] != '\0')
			{
				if (str[i] == '$' && quote == '"' && str[i + 1] != 32)
					str = replace_env(str, i, env_list);
				i++;
			}
		}
		str = replace(str, i, env_list);
	}
	return (str);
}

char	*replace_env(char *str, int i, t_env_list *env_list)
{
	int		j;
	char	*env;
	char	*new_env;
	char	*end_str;

	j = 0;
	str[i++] = '\0';
	env = str + i;
	end_str = NULL;
	while (env[j] && env[j] != '\0' && env[j] != 32
		&& env[j] != '"' && env[j] != '$' && env[j] != '\'')
	{
		j++;
	}
	new_env = ft_calloc(j + 1, sizeof(char *));
	ft_memcpy(new_env, env, j);
	if (env[j] == '\0')
		end_str = NULL;
	else
	{
		end_str = env + j;
	}
	return (ft_new_str(str, new_env, end_str, env_list));
}

char	*ft_new_str(char *str, char *env, char *end_str, t_env_list *env_list)
{
	char	*new_str;
	char	*new_env;
	char	*temp;

	if (ft_isdigit(env[0]))
		new_str = ft_strjoin(str, env + 1);
	else if (ft_getenv(env, env_list))
	{
		new_env = ft_getenv(env, env_list)->value;
		new_str = ft_strjoin(str, new_env);
	}
	else
		new_str = ft_strjoin(str, "\0");
	if (end_str != NULL)
	{
		temp = new_str;
		new_str = ft_strjoin(new_str, end_str);
		free(temp);
	}
	free(env);
	free(str);
	return (new_str);
}

t_env_list	*ft_getenv(char *env, t_env_list *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(env, env_list->name, ft_strlen(env))
			&& ft_strlen(env) == ft_strlen(env_list->name))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
