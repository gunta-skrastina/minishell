/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:57:31 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 20:10:07 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env(t_env_list *env)
{
	char	**envp;
	int		i;
	char	*temp;

	envp = ft_calloc(count_env(env) + 1, sizeof(char **));
	i = 0;
	while (env)
	{
		envp[i] = ft_strjoin(env->name, "=");
		temp = envp[i];
		envp[i] = ft_strjoin(envp[i], env->value);
		free(temp);
		env = env->next;
		i++;
	}
	return (envp);
}

int	count_env(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**split_argv(char *str)
{
	int		i;
	char	**split;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i += ft_charcmp(str + i + 1, str[i]) + 1;
		else if (str[i] == 32)
			str[i] = '\t';
		i++;
	}
	split = ft_split(str, '\t');
	free(str);
	i = 0;
	while (split[i] != NULL)
	{
		if (split[i][0] == '"' || split[i][0] == '\'')
			split[i] = without_quotes(split[i]);
		i++;
	}
	return (split);
}

int	ft_handle_filesonly(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (cmd->cmd[0] == '\0' && cmd->in)
	{
		i = ft_in_validation(cmd, &fd, cmd->in);
		if (i == 1)
			i = 0;
		else
			i = 1;
		if (fd != STDIN_FILENO)
			close(fd);
	}
	else if (cmd->cmd[0] == '\0' && cmd->out)
	{
		i = ft_out_validation(cmd, &fd);
		if (i == 1)
			i = 0;
		if (fd != STDOUT_FILENO)
			close(fd);
	}
	return (i);
}

void	ft_choose_exec(t_cmd *cmd, char **argv, char **envp, t_env_list *env)
{
	if (!cmd->lim.name && (!cmd->in || !cmd->in[0])
		&& (!cmd->out || !cmd->out[0].name))
			g_err = execve(argv[0], argv, envp);
	else if (cmd->here_doc)
		ft_parce_limcmd(cmd, argv, env, envp);
	else
		g_err = ft_redirect(cmd, argv);
}
