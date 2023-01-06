/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:58:57 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/06 19:14:05 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort(t_env_list *env_list, int size);

void	export(t_env_list *env_list)
{
	int			i;
	int			size;
	t_env_list	*head;

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
			env_list = env_list->next;
		else
			env_list = head;
	}
}

static void	sort(t_env_list *env_list, int size)
{
	t_env_list	*max;
	t_env_list	*temp;
	int			i;

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
