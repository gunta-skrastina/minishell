/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:35:40 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/03 10:08:13 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_charcmp(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_charcmp_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i += ft_charcmp(str + i + 1, str[i]) + 1;
		else if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
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

char	*split_inout(char const *s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != 32 && s[i] != '>' && s[i] != '<')
		i++;
	str = ft_calloc(i + 2, sizeof(char *));
	ft_strlcpy(str, s, i + 1);
	return (str);
}

int	ft_is_builtin(char *str)
{
	if ((!ft_strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		|| (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		|| (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		|| (!ft_strncmp(str, "export", 6) && ft_strlen(str) == 6)
		|| (!ft_strncmp(str, "unset", 5) && ft_strlen(str) == 5)
		|| (!ft_strncmp(str, "env", 3) && ft_strlen(str) == 3)
		|| (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == 4))
		return (1);
	else
		return (0);
}
