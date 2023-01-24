/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:09:08 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/24 14:19:27 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env_list *env);
static void	find_node(t_env_list *env_list, char *split);

void	unset(t_env_list *env_list, char *vars)
{
	char		**split;
	int			i;
	t_env_list	*head;

	i = 0;
	split = ft_split(vars, 32);
	head = env_list;
	while (split[i])
	{
		env_list = head;
		find_node(env_list, split[i]);
		i++;
	}
	ft_free_split(split, 0);
}

static void	free_env_node(t_env_list *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

static void	find_node(t_env_list *env_list, char *split)
{
	t_env_list	*previous;
	t_env_list	*temp;

	previous = NULL;
	while (env_list)
	{
		if (!ft_strncmp(env_list->name, split, ft_strlen(split))
			&& ft_strlen(split) == ft_strlen(env_list->name))
		{
			if (previous)
			{
				previous->next = env_list->next;
				free_env_node(env_list);
			}
			else
			{
				temp = env_list;
				env_list = env_list->next;
				free_env_node(temp);
			}
			break ;
		}
		previous = env_list;
		env_list = env_list->next;
	}
}
