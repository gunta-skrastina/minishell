/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:37:49 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/09 14:56:19 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_env(char const *s, char c)
{
	char	**env;
	int		len_name;
	int		len_value;
	
	if (!s)
		return (NULL);
	env = ft_calloc(2, sizeof(char **));
	len_name = ft_charcmp(s, c) + 1;
	len_value = ft_strlen(s) - len_name + 2;
	env[0] = ft_calloc(len_name, sizeof(char *));
	env[1] = ft_calloc(len_value, sizeof(char *));
	ft_strlcpy(env[0], s, len_name);
	ft_strlcpy(env[1], s + len_name, len_value);
	return (env);
}
