/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:09:08 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/06 19:11:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env_list *env_list, char *cmd)
{
	t_env_list	*previous;
	t_env_list	*head;

	previous = NULL;
	head = env_list;
	while (env_list)
	{
		if (!ft_strncmp(env_list->name, cmd, ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen(env_list->name))
		{
			if (previous)
			{
				previous->next = env_list->next;
				free(env_list);
			}
			else
			{
				head = env_list->next;
				free(env_list);
			}
			break ;
		}
		previous = env_list;
		env_list = env_list->next;
	}
}
