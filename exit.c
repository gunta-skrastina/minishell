/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:38:43 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/14 02:37:23 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd, t_env_list *env)
{
	t_cmd		*temp_cmd;
	t_env_list	*temp_env;

	while (cmd)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		free(temp_cmd);
	}
	while (env)
	{
		temp_env = env;
		env = env->next;
		free(temp_env);
	}
	exit(0);
}
