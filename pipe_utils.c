/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:21:45 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/05 18:40:14 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lim_inchild(int pip[2], t_cmd *cmd)
{		
	int	proc;

	proc = fork();
	if (proc < 0)
		perror("Forking error");
	else if (proc == 0)
	{
		close(pip[0]);
		ft_collect_topipe(pip, cmd);
		close(pip[1]);
		exit(0);
	}
	wait(NULL);
	return ;
}

void	ft_first_pipe(t_cmd *cmd, t_env_list *env, int pip[2])
{
	close(pip[0]);
	if (cmd && cmd->here_doc)
		ft_lim_inchild(pip, cmd);
	if (cmd && cmd->next && ((cmd->next)->cmd[0] != '\0'
			|| (cmd->next)->in || (cmd->next)->here_doc || (cmd->next)->out))
	{
		if (dup2(pip[1], STDOUT_FILENO) < 0)
		{
			perror("Output duplication error");
			exit(0);
		}
	}
	execute_builtins(cmd, env);
	close(pip[1]);
	exit(0);
	return ;
}

void	ft_last_pipe(t_cmd *cmd, t_env_list *env, int pip[2])
{
	if (dup2(pip[0], STDIN_FILENO) < 0)
	{
		perror("Input duplication error");
		exit(0);
	}
	execute_builtins(cmd, env);
	close(pip[0]);
	exit(0);
	return ;
}

void	ft_middle_pipe(t_cmd *cmd, t_env_list *env, int pip[2], int pip2[2])
{
	close(pip[1]);
	if (dup2(pip[0], STDIN_FILENO) < 0)
	{
		perror("Input duplication error");
		exit(0);
	}
	if (cmd && cmd->here_doc)
		ft_lim_inchild(pip2, cmd);
	close(pip2[0]);
	if (dup2(pip2[1], STDOUT_FILENO) < 0)
	{
		perror("Output duplication error");
		exit(0);
	}
	if (g_err == 130)
	{
		close(pip2[1]);
		exit(0);
	}
	execute_builtins(cmd, env);
	close(pip[0]);
	close(pip[1]);
	close(pip2[1]);
	exit(0);
	return ;
}
