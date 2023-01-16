/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:45:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 14:27:40 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_cmd *cmd, t_env_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4) && ft_strlen(cmd->cmd) == 4)
		echo(cmd->vars);
	else if (!ft_strncmp(cmd->cmd, "cd", 2) && ft_strlen(cmd->cmd) == 2)
		cd(cmd->vars, env_list);
	else if (!ft_strncmp(cmd->cmd, "pwd", 2) && ft_strlen(cmd->cmd) == 3)
		pwd();
	else if (!ft_strncmp(cmd->cmd, "export", 6) && ft_strlen(cmd->cmd) == 6)
		export(env_list, cmd->vars);
	else if (!ft_strncmp(cmd->cmd, "unset", 5) && ft_strlen(cmd->cmd) == 5)
		unset(env_list, cmd->vars);
	else if (!ft_strncmp(cmd->cmd, "env", 3) && ft_strlen(cmd->cmd) == 3)
		env(env_list);
	else if (!ft_strncmp(cmd->cmd, "exit", 4) && ft_strlen(cmd->cmd) == 4)
		ft_exit(cmd, env_list);
	else if (cmd->cmd[0] == '\0')
		return (0);
	else
		printf("minishell: %s: command not found\n", cmd->cmd);
	return (0);
}
