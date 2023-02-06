/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:38:38 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 20:40:44 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_check(t_cmd *cmd);

int	ft_error(char *cmd, char *path, char *err)
{
	if (!path)
		printf("minishell: %s: %s\n", cmd, err);
	else
		printf("minishell: %s: %s: %s\n", cmd, path, err);
	return (1);
}

void	ft_handle_unexisting(t_cmd *cmd)
{
	if (cmd->here_doc)
	{
		cmd->lim.num = -2;
		g_err = 1;
		ft_parce_limcmd(cmd, NULL, NULL, NULL);
	}
	printf("minishell: %s: command not found\n", cmd->cmd);
}

int	handle_errno(t_cmd *cmd, int err)
{
	char	*str;

	if (err_check(cmd) == 0)
		return (0);
	str = ft_strjoin("minishell: ", cmd->cmd);
	g_err = 127;
	if ((err == 2 && (cmd->cmd[0] != '/')))
		ft_handle_unexisting(cmd);
	else
	{
		if (err == 13 && cmd->cmd[0] == '/')
		{
			printf("minishell: %s: is a directory\n", cmd->cmd);
			g_err = 126;
		}
		else
			perror(str);
		free(str);
		exit(g_err);
	}
	free(str);
	return (g_err);
}

int	handle_in(char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	return (1);
}

static int	err_check(t_cmd *cmd)
{
	if (ft_charcmp(cmd->cmd, 32) != -1)
	{
		g_err = 127;
		printf("minishell: %s: command not found\n", cmd->cmd);
	}
	if (g_err == 130 && !ft_is_builtin(cmd->cmd) && cmd->lim.name)
		exit(1);
	else if (g_err == 0 || g_err == 1 || g_err == 126
		|| g_err == 127 || g_err == 130 || g_err == 131
		|| (!ft_strncmp(cmd->cmd, "make", 4) && ft_strlen(cmd->cmd) == 4))
		return (0);
	return (-1);
}
