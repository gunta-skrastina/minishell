/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:53:54 by htoustsi          #+#    #+#             */
/*   Updated: 2023/01/24 23:12:10 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_fork(int pip1[2], int pip2[2], t_cmd *cmd, t_env_list *env_list)
{
	int	proc;

	proc = fork();
	if (proc < 0)
		perror("Forking error");
	else if (proc == 0)
	{
		if (pip1[1] && pip1[1] != STDOUT_FILENO)
			close(pip1[1]);
		if (pip2[0] && pip2[0] != STDIN_FILENO)
			close(pip2[0]);
		ft_cmd_exec(cmd, pip1[0], pip2[1], env_list);
	}
	return ;
}

void	ft_pipe(t_cmd *cmd, int pip1[2], int fd[2], t_env_list *env_list)
{
	int	pip2[2];
//	int	count;

//	count = 1;
//	if (argv[0][0] == 'h')
//		count = 2;
//	while (count < (argc - 2))
	while (cmd && cmd->cmd)
	{
		pipe(pip2);
		ft_create_fork(pip1, pip2, cmd, env_list);
		if (pip2[0] && pip2[0] != STDIN_FILENO)
		{
			close(pip1[0]);
			if (dup2(pip2[0], pip1[0]) < 0)
			{
				perror("Pipes duplication error");
				exit(0);
			}
		}
		if (pip1[1] && pip1[1] != STDOUT_FILENO)
		{
			close(pip1[1]);
			if (dup2(pip2[1], pip1[1]) < 0)
			{
				perror("Pipes duplication error");
				exit(0);
			}
		}
//		if ((dup2(pip2[0], pip1[0]) < 0) || (dup2(pip2[1], pip1[1]) < 0))
//		{
//			perror("Pipes duplication error");
//			exit(0);
//		}
//		if (pip2[0] && pip2[0] != STDIN_FILENO)
		close(pip2[0]);
//		if (pip2[1] && pip2[1] != STDOUT_FILENO)
		close(pip2[1]);
		wait(NULL);
//		++count;
		cmd = cmd->next;
	}
	ft_create_fork(pip1, fd, cmd, env_list);
//	if (pip1[0] && pip1[0] != STDIN_FILENO)
		close(pip1[0]);
//	if (pip1[1] && pip1[1] != STDOUT_FILENO)
		close(pip1[1]);
}
