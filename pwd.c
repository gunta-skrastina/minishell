/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:02:51 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/04 21:48:10 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_cmd *cmd, int fd_out, int proc)
{
	char	*cwd;

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
		cwd = getcwd(NULL, 1);
		printf("%s\n", cwd);
		free(cwd);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		exit(0);
	}
	wait(NULL);
	return (0);
}
