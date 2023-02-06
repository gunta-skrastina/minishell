/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:58:57 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 13:18:10 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort(t_env_list *env, int size);
static void	zero_num(t_env_list *env);

int	export(t_cmd *cmd, t_env_list *env, char *vars, int proc)
{
	int			size;
	int			fd_out;

	if (ft_in_validation(cmd, &fd_out, cmd->in) < 0)
		return (1);
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	if (!vars || !vars[0])
	{
		size = ft_env_lstsize(env);
		sort(env, size);
		proc = fork();
		if (proc == 0)
			ft_file_export(size, env, cmd);
		wait(NULL);
	}
	else
	{
		if (ft_out_validation(cmd, &fd_out) < 0)
			return (1);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		export_add(env, vars);
	}
	return (0);
}

static void	sort(t_env_list *env, int size)
{
	t_env_list	*max;
	t_env_list	*temp;
	int			i;

	temp = env;
	zero_num(env);
	i = size;
	max = env;
	while (i > 0)
	{
		temp = env;
		while (temp)
		{
			if (ft_strncmp(temp->name, max->name,
					ft_strlen(temp->name)) > 0 && temp->num == 0)
				max = temp;
			temp = temp->next;
		}
		max->num = i;
		temp = env;
		while (temp->num != 0 && temp->next)
			temp = temp->next;
		max = temp;
		i--;
	}
}

void	export_env(t_env_list *env, char *vars)
{
	t_env_list	*new_env;
	char		*name;
	char		*value;
	char		**new_var;

	new_var = split_env(vars, '=');
	name = new_var[0];
	value = new_var[1];
	if (ft_strlen(name) > 0)
	{
		new_env = ft_getenv(name, env);
		if (new_env)
		{
			free(new_env->value);
			new_env->value = value;
		}
		else
			ft_env_lstadd_back(&env, ft_env_lstnew(name, value));
	}
	free(new_var);
}

void	export_add(t_env_list *env, char *vars)
{
	int		i;
	char	**split;
	char	*temp;

	i = -1;
	temp = ft_strjoin(vars, "\0");
	split = split_argv(temp);
	while (split[++i])
		split[i] = without_quotes(split[i]);
	i = 0;
	while (split[i])
	{
		if (check_if_valid_env(split[i]) == -1 || split[i][0] == '=')
			printf("minishell: %s: `%s\': %s\n",
				"export", split[i], "not a valid identifier");
		else if (ft_charcmp(split[i], '=') == -1)
			;
		else
			export_env(env, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

static void	zero_num(t_env_list *env)
{
	while (env)
	{
		env->num = 0;
		env = env->next;
	}
}
