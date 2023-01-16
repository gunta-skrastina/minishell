/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 00:36:42 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 13:59:55 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_env_lstnew(char *name, char *value)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env_list	*ft_env_lstlast(t_env_list *lst)
{
	t_env_list	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*current;

	if (*lst)
	{
		current = *lst;
		current = ft_env_lstlast(current);
		current->next = new;
	}
	else
		*lst = new;
}

int	ft_env_lstsize(t_env_list *lst)
{
	t_env_list	*current;
	int			count;

	current = lst;
	count = 0;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

void	free_env_list(t_env_list *env)
{
	t_env_list	*temp_env;

	while (env)
	{
		temp_env = env;
		env = env->next;
		free(temp_env->name);
		free(temp_env->value);
		free(temp_env);
	}
}
