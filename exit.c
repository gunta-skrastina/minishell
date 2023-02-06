/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:38:43 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/04 20:15:08 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_valid(char *str);

void	ft_exit(t_cmd *cmd, t_env_list *env)
{
	int	exit_status;
	int	fd_out;

	if (ft_in_validation(cmd, &fd_out, cmd->in) < 0)
		return ;
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	if (ft_out_validation(cmd, &fd_out) < 0)
		return ;
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	exit_status = 0;
	if (cmd->vars != NULL)
		exit_status = check_if_valid(cmd->vars);
	if (exit_status != 255 && cmd->vars)
		exit_status = ft_atoi(cmd->vars);
	if (exit_status > 255)
		exit_status %= 256;
	free_cmd(cmd);
	free_env_list(env);
	if (exit_status == 0)
		printf("exit\n");
	else
		printf("exit %d\n", exit_status);
	exit(exit_status);
}

static int	check_if_valid(char *str)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (ft_isdigit(str[i]))
				i++;
			else
			{
				printf("minishell: exit: %s: numeric argument required\n", str);
				exit_status = 255;
				break ;
			}
		}
	}
	return (exit_status);
}
