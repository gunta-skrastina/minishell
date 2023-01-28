/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:35:40 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/28 15:57:27 by gskrasti         ###   ########.fr       */
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
