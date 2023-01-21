/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:58:57 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/21 04:58:56 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort(t_env_list *env, int size);
static void	zero_num(t_env_list *env);

void	export(t_env_list *env, char *vars)
{
	int			i;
	int			size;
	t_env_list	*head;

	if (!vars || !vars[0])
	{
		i = 1;
		head = env;
		size = ft_env_lstsize(env);
		sort(env, size);
		while (size >= i)
		{
			if (env->num == i)
			{
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
				i++;
			}
			if (env->next)
				env = env->next;
			else
				env = head;
		}
	}
	else
		export_add(env, vars);
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

	i = 0;
	split = ft_split(vars, 32);
	while (split[i])
	{
		if (split[i][0] == '=' || ft_isdigit(split[i][0]))
			printf("minishell: %s: `%s\': %s\n",
				"export", split[i], "not a valid identifier");
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
