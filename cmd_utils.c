/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:51:49 by htoustsi          #+#    #+#             */
/*   Updated: 2023/01/24 23:13:28 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline_fd(int fd)
{
	char	symbol;
	int		ind;
	char	*line;

	line = (char *)malloc(sizeof(char) * 4097);
	if (!line)
	{	
		perror("Memory allocation error");
		exit(0);
		return (NULL);
	}
	ind = 0;
	while (read(fd, &symbol, sizeof(char)) > 0 && symbol != '\n' && ind < 4097)
	{
		line[ind] = symbol;
		++ind;
	}
	line[ind] = '\n';
	line[ind + 1] = '\0';
	return (line);
}

void	ft_getline_cmd(int pip[2], char *limiter)
{
	char	*line;

	close(pip[0]);
	ft_putstr_fd("> ", 1);
	line = ft_readline_fd(1);
	while ((ft_strlen(line) - ft_strlen(limiter) != 1)
		|| (ft_strncmp(line, limiter, ft_strlen(line) - 1) != 0))
	{
		write(pip[1], line, ft_strlen(line));
		free(line);
		ft_putstr_fd("> ", 1);
		line = ft_readline_fd(1);
	}
	free(line);
	close(pip[1]);
	exit(0);
	wait(NULL);
	return ;
}

void	ft_cmd_exec(t_cmd *cmd, int in_fd, int out_fd, t_env_list *env_list)
{
//	char	*args[4];

    if ((in_fd != STDIN_FILENO) && (dup2(in_fd, STDIN_FILENO) < 0))
	{
		perror("Duplication stdin error");
		exit(0);
		return ;
	}
    if ((out_fd != STDOUT_FILENO) && (dup2(out_fd, STDOUT_FILENO) < 0))
	{
		perror("Duplication out error");
		exit(0);
		return ;
	}
	execute_path(cmd, env_list);
//    if (dup2(in_fd, STDIN_FILENO) < 0 || dup2(out_fd, STDOUT_FILENO) < 0)
//	{
//		perror("Duplication stdin/out error");
//		exit(0);
//		return ;
//	}
//    if (in_fd != STDIN_FILENO)
//	    close(in_fd);
//    if (out_fd != STDOUT_FILENO)
//	    close(out_fd);
//	args[0] = "/bin/sh";
//	args[1] = "-c";
//	args[2] = cmd;
//	args[3] = NULL;
//	if (execve(args[0], (char *const *)args, NULL) < 0)
//		perror("Bash error");
//	close(in_fd);
//	close(out_fd);
	return ;
}
