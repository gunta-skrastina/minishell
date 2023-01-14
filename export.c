/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:58:57 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/14 02:38:57 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort(t_env_list *env_list, int size);

void	export(t_env_list *env_list, char *vars)
{
	int			i;
	int			size;
	t_env_list	*head;
	char		**split;

	if (!vars || !vars[0])
	{
		i = 1;
		head = env_list;
		size = ft_env_lstsize(env_list);
		sort(env_list, size);
		while (size >= i)
		{
			if (env_list->num == i)
			{
				printf("declare -x %s=\"%s\"\n", env_list->name, env_list->value);
				i++;
			}
			if (env_list->next)
			{
				env_list = env_list->next;
			}
			else
			{
				env_list = head;
			}
		}
	}
	else
	{
		i = 0;
		split = ft_split(vars, 32);
		while (split[i])
		{
			if (split[i][0] == '=')
			{
				printf("minishell: %s: `%s\': %s\n", "export", split[i], "not a valid identifier");
			}
			else
				export_env(env_list, split[i]);
			i++;
		}
	}
}

static void	sort(t_env_list *env_list, int size)
{
	t_env_list	*max;
	t_env_list	*temp;
	int			i;

	temp = env_list;
	while (temp)
	{
		temp->num = 0;
		temp = temp->next;
	}
	i = size;
	max = env_list;
	while (i > 0)
	{
		temp = env_list;
		while (temp)
		{
			if (ft_strncmp(temp->name, max->name,
					ft_strlen(temp->name)) > 0 && temp->num == 0)
				max = temp;
			temp = temp->next;
		}
		max->num = i;
		temp = env_list;
		while (temp->num != 0 && temp->next)
			temp = temp->next;
		max = temp;
		i--;
	}
}

void	export_env(t_env_list *env_list, char *vars)
{
	t_env_list	*env;
	char		*name;
	char		*value;
	char		**new_var;

	new_var = split_env(vars, '=');
	name = new_var[0];
	value = new_var[1];
	if (ft_strlen(name) > 0)
	{
		env = ft_getenv(name, env_list);
		if (env)
		{
			free(env->value);
			env->value = value;
		}
		else
		{
			ft_env_lstadd_back(&env_list, ft_env_lstnew(name, value));
		}
	}
}
