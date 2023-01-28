/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:45:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/28 19:02:49 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(t_cmd *cmd, t_env_list *env_list)
{
	g_err = 0;
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
	{
		printf("minishell: %s: command not found\n", cmd->cmd);
		g_err = 127;
	}
	return (0);
}

int	execute_path(t_cmd *cmd, t_env_list *env)
{
	pid_t	pid;
	int		i;
	char	**argv;
	char	*str;
	char	*temp;

	str = ft_strjoin(cmd->cmd, " ");
	if (cmd->vars != NULL)
	{
		temp = str;
		str = ft_strjoin(str, cmd->vars);
		free(temp);
		argv = ft_split(str, 32);
	}
	else
	{
		argv = NULL;
		argv[0] = cmd->cmd;
		argv[1] = NULL;
	}
	i = access(cmd->cmd, X_OK);
	if (i == -1 && ft_getenv("PATH", env) != NULL)
		argv[0] = find_path(argv[0], env);
	if (!i || (argv[0] != NULL && ft_getenv("PATH", env) != NULL))
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if ((!cmd->in || !cmd->in[0]) && (!cmd->out || !cmd->out[0].name))
				execve(argv[0], argv, NULL);
			else
				ft_redirect(cmd, argv);
		}
		else
			wait(NULL);
		ft_free_split(argv, 0);
		free(str);
		return (0);
	}
	ft_free_split(argv, 0);
	free(str);
	return (-1);
}

char	*find_path(char *cmd, t_env_list *env)
{
	int		i;
	int		j;
	char	**path;
	char	*just_cmd;
	char	*temp;

	just_cmd = cmd;
	path = ft_split(ft_getenv("PATH", env)->value, ':');
	i = -1;
	j = 0;
	while (i == -1 && path[j] != NULL)
	{
		temp = path[j];
		path[j] = ft_strjoin(path[j], "/");
		free(temp);
		cmd = ft_strjoin(path[j], just_cmd);
		i = access(cmd, X_OK);
		if (i == -1)
			free(cmd);
		j++;
	}
	ft_free_split(path, 0);
	free(just_cmd);
	if (i == -1)
		return (NULL);
	return (cmd);
}

void	ft_redirect(t_cmd *cmd, char **argv)
{
	int	fd_in;
	int	fd_out;

	if (ft_invalidation(cmd, &fd_in, cmd->in) < 0)
		return ;
    if (ft_outvalidation(cmd, &fd_out) < 0)
        return ;
	execve(argv[0], argv, NULL);
	return ;
}
