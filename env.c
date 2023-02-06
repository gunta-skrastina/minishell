/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:56:33 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/04 21:46:57 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_cmd *cmd, t_env_list *env_list, int fd_out, int proc)
{
	if (ft_in_validation(cmd, &fd_out, cmd->in) < 0)
		return (1);
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	proc = fork();
	if (proc == 0)
	{
		if ((ft_out_validation(cmd, &fd_out) < 0)
			|| (!ft_clone_inout(fd_out, STDOUT_FILENO)))
		{
			exit(0);
			return (1);
		}
		while (env_list)
		{
			printf("%s=%s\n", env_list->name, env_list->value);
			env_list = env_list->next;
		}
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		exit(0);
	}
	wait(NULL);
	return (0);
}
