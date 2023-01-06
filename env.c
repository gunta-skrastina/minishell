/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:56:33 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/04 14:03:16 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_env_list *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->env_name, env_list->env_value);
		env_list = env_list->next;
	}
}

