/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 00:36:42 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/02 01:16:56 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_env_lstnew(char *env_name, char *env_value)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->env_name = env_name;
    new_node->env_value = env_value;
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

void	ft_env_lstdelone(t_env_list *lst)
{
	free(lst->env_name);
	free(lst->env_value);
    // ft_bzero(lst->env_name, ft_strlen(lst->env_name));
	// ft_bzero(lst->env_value, ft_strlen(lst->env_value));
	free(lst);
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
