/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:53:54 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/05 19:26:16 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_execute_pipechain(t_cmd *cmd, t_env_list *env,
			int *fd_in, int *fd_out)
{
	int	proc;
	int	pip[2];
	int	pip2[2];

	while (cmd && cmd->next && ((cmd->next)->cmd[0] != '\0'
			|| (cmd->next)->lim.name || (cmd->next)->in || (cmd->next)->out))
	{
		pip[0] = *fd_in;
		pip[1] = *fd_out;
		pipe(pip2);
		close(pip[1]);
		proc = fork();
		if (proc < 0)
			perror("Forking error");
		else if (proc == 0)
			ft_middle_pipe(cmd, env, pip, pip2);
		wait(NULL);
		if (g_err == 130)
			return (NULL);
		close(pip[0]);
		*fd_in = pip2[0];
		*fd_out = pip2[1];
		cmd = cmd->next;
	}
	return (cmd);
}

void	ft_pipe_new(t_cmd *cmd, t_env_list *env)
{
	int	pip[2];
	int	proc;

	pipe(pip);
	proc = fork();
	if (proc < 0)
		perror("Forking error");
	else if (proc == 0)
		ft_first_pipe(cmd, env, pip);
	wait(NULL);
	if (cmd && cmd->next && ((cmd->next)->cmd[0] != '\0'
			|| (cmd->next)->lim.name || (cmd->next)->in
			|| (cmd->next)->out))
		cmd = ft_execute_pipechain(cmd->next, env, &pip[0], &pip[1]);
	close(pip[1]);
	proc = fork();
	if (proc < 0)
		perror("Forking error");
	else if (proc == 0)
		ft_last_pipe(cmd, env, pip);
	wait(NULL);
	close(pip[0]);
	return ;
}
