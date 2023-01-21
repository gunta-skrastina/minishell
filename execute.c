/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:45:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/21 12:14:17 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_cmd *cmd, t_env_list *env_list)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4) && ft_strlen(cmd->cmd) == 4)
		echo(cmd->vars);
	else if (!ft_strncmp(cmd->cmd, "cd", 2) && ft_strlen(cmd->cmd) == 2)
		cd(cmd->vars, env_list);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3) && ft_strlen(cmd->cmd) == 3)
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
	else if (!execute_path(cmd, env_list))
		;
	else
		printf("minishell: %s: command not found\n", cmd->cmd);
	return (0);
}

int	execute_path(t_cmd *cmd, t_env_list *env)
{
	pid_t	pid;
	int		i;
	char	*argv[3];

	i = -1;
	argv[0] = cmd->cmd;
	if (cmd->vars[0])
		argv[1] = cmd->vars;
	else
		argv[1] = NULL;
	argv[2] = NULL;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		i = execve(cmd->cmd, argv, NULL);
		if (i == -1 && ft_getenv("PATH", env) != NULL)
			i = find_path(argv, cmd, env);
		return (i);
	}
	else
		wait(NULL);
	return (0);
}

int	find_path(char **argv, t_cmd *cmd, t_env_list *env)
{
	int		i;
	int		j;
	char	**path;

	path = ft_split(ft_getenv("PATH", env)->value, ':');
	i = -1;
	j = 0;
	while (i == -1 && path[j] != NULL)
	{
		path[j] = ft_strjoin(path[j], "/");
		argv[0] = ft_strjoin(path[j], cmd->cmd);
		i = execve(argv[0], argv, NULL);
		j++;
	}
	j = -1;
	while (path[++j])
		free(path[j]);
	free(path);
	if (i == -1)
		return (i);
	return (0);
}
