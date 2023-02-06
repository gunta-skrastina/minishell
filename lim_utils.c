/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:51:49 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/05 18:40:22 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline_fd(int fd, int ind)
{
	char	symbol;
	char	*line;

	line = (char *)malloc(sizeof(char) * 4097);
	if (!line)
	{	
		perror("Memory allocation error");
		return (NULL);
	}
	while (read(fd, &symbol, sizeof(char)) > 0)
	{
		if (symbol != '\n' && symbol != 3 && symbol != 4 && ind < 4094)
		{
			line[ind] = symbol;
			++ind;
		}
		else
		{
			line[ind] = symbol;
			line[ind + 1] = '\0';
			return (line);
		}
	}
	free(line);
	return (NULL);
}

void	ft_getline_cmd(int pip[2], char *limiter)
{
	char	*line;
	int		len;

	ft_putstr_fd("> ", 1);
	line = ft_readline_fd(1, 0);
	len = ft_strlen(limiter);
	while (g_err != 130 && line && ((ft_strlen(line) - len != 1)
			|| (ft_strncmp(line, limiter, len - 1) != 0)))
	{
		write(pip[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("> ", 1);
		line = ft_readline_fd(1, 0);
	}
	if (line)
		free(line);
	return ;
}

int	ft_collect_topipe(int pip1[2], t_cmd *cmd)
{
	ft_getline_cmd(pip1, cmd->lim.name);
	if (pip1[1] != STDOUT_FILENO)
		close(pip1[1]);
	if (cmd->cmd[0] == '\0' || g_err == 130)
	{
		close(pip1[0]);
		return (0);
	}
	return (1);
}

int	ft_execute_fromlim(t_cmd *cmd, int pip1[2], char **argv, char **envp)
{
	int	fd_out;

	if (ft_out_validation(cmd, &fd_out) < 0)
		return (-1);
	if ((fd_out != STDOUT_FILENO) && (dup2(fd_out, STDOUT_FILENO) < 0))
	{
		perror("Duplication stdout error");
		return (-1);
	}
	if ((pip1[0] != STDIN_FILENO) && (dup2(pip1[0], STDIN_FILENO) < 0))
	{
		perror("Duplication stdin error");
		return (-1);
	}
	if (cmd->cmd[0] != '\0' && g_err != 130)
		execve(argv[0], argv, envp);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (pip1[0] != STDIN_FILENO)
		close(pip1[0]);
	return (1);
}

int	ft_parce_limcmd(t_cmd *cmd, char **argv, t_env_list *env, char **envp)
{
	int	pip1[2];
	int	out;

	pipe(pip1);
	if (!ft_collect_topipe(pip1, cmd))
		return (1);
	if ((cmd->lim.num == ft_num_infiles(cmd) - 1) && (!ft_is_builtin(cmd->cmd)))
	{
		out = ft_execute_fromlim(cmd, pip1, argv, envp);
		exit(0);
		if (out != 1)
			return (-1);
	}
	else if (g_err != 130)
	{
		cmd->here_doc = 0;
		cmd->lim.name = NULL;
		cmd->lim.num = -2;
		execute_builtins(cmd, env);
		if (!ft_is_builtin(cmd->cmd))
			exit(0);
	}
	if (!ft_is_builtin(cmd->cmd) && (g_err == 0 || g_err == 130))
		exit(0);
	return (1);
}
