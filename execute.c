/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:45:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 10:58:43 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execution(t_cmd *cmd, char **argv, t_env_list *env);

int	execute_builtins(t_cmd *cmd, t_env_list *env_list)
{
	if (cmd && cmd->cmd && (ft_is_builtin(cmd->cmd)
			|| cmd->cmd[0] == '\0') && cmd->lim.name)
		ft_parce_limcmd(cmd, NULL, env_list, NULL);
	else if (!ft_strncmp(cmd->cmd, "echo", 4) && ft_strlen(cmd->cmd) == 4)
		g_err = echo(cmd, STDOUT_FILENO, 0);
	else if (!ft_strncmp(cmd->cmd, "cd", 2) && ft_strlen(cmd->cmd) == 2)
		g_err = cd(cmd->vars, env_list, cmd, STDOUT_FILENO);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3) && ft_strlen(cmd->cmd) == 3)
		g_err = pwd(cmd, STDOUT_FILENO, 1);
	else if (!ft_strncmp(cmd->cmd, "export", 6) && ft_strlen(cmd->cmd) == 6)
		g_err = export(cmd, env_list, cmd->vars, 1);
	else if (!ft_strncmp(cmd->cmd, "unset", 5) && ft_strlen(cmd->cmd) == 5)
		g_err = unset(env_list, cmd->vars, cmd, STDOUT_FILENO);
	else if (!ft_strncmp(cmd->cmd, "env", 3) && ft_strlen(cmd->cmd) == 3)
		g_err = env(cmd, env_list, STDOUT_FILENO, 1);
	else if (!ft_strncmp(cmd->cmd, "exit", 4) && ft_strlen(cmd->cmd) == 4)
		ft_exit(cmd, env_list);
	else if (cmd->cmd[0] == '\0' && (cmd->in || cmd->out))
		g_err = ft_handle_filesonly(cmd);
	else if (cmd->cmd[0] == '\0')
		return (0);
	else if (ft_charcmp(cmd->cmd, 32) == -1)
		g_err = execute_path(cmd, env_list);
	handle_errno(cmd, errno);
	return (0);
}

int	execute_path(t_cmd *cmd, t_env_list *env)
{
	int		i;
	char	**argv;
	char	*str;
	char	*temp;
	int		ret;

	ret = -1;
	g_err = 0;
	str = ft_strjoin(cmd->cmd, " ");
	if (cmd->vars != NULL)
	{
		temp = str;
		str = ft_strjoin(str, cmd->vars);
		free(temp);
	}
	argv = split_argv(str);
	i = access(cmd->cmd, X_OK);
	if (i == -1 && ft_getenv("PATH", env) != NULL && cmd->cmd[0] != '/')
		argv[0] = find_path(argv[0], env);
	if (!i || (argv[0] != NULL && ft_getenv("PATH", env) != NULL))
		ret = execution(cmd, argv, env);
	free(argv[0]);
	ft_free_split(argv, 1);
	return (ret);
}

static int	execution(t_cmd *cmd, char **argv, t_env_list *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	status = 0;
	g_err = 0;
	envp = convert_env(env);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_choose_exec(cmd, argv, envp, env);
	else
	{
		waitpid(pid, &status, 0);
		if (status == 256)
			g_err = 1;
		if (WIFEXITED(status))
			g_err = WEXITSTATUS(status);
		ft_free_split(envp, 0);
	}
	return (g_err);
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
	j = -1;
	while (i == -1 && path[++j] != NULL)
	{
		temp = path[j];
		path[j] = ft_strjoin(path[j], "/");
		free(temp);
		cmd = ft_strjoin(path[j], just_cmd);
		i = access(cmd, X_OK);
		if (i == -1)
			free(cmd);
	}
	ft_free_split(path, 0);
	free(just_cmd);
	if (i == -1)
		return (NULL);
	return (cmd);
}

int	ft_redirect(t_cmd *cmd, char **argv)
{
	int	fd_in;
	int	fd_out;

	if (ft_in_validation(cmd, &fd_in, cmd->in) < 0)
		return (-1);
	if (ft_out_validation(cmd, &fd_out) < 0)
		return (-1);
	if ((fd_in != STDIN_FILENO) && (dup2(fd_in, STDIN_FILENO) < 0))
	{
		perror("Duplication stdin error");
		exit(0);
		return (-1);
	}
	if ((fd_out != STDOUT_FILENO) && (dup2(fd_out, STDOUT_FILENO) < 0))
	{
		perror("Duplication stdout error");
		exit(0);
		return (-1);
	}
	g_err = execve(argv[0], argv, NULL);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (g_err);
}
