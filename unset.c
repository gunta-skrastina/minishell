/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:09:08 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 14:39:40 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env_list *env_list, char *vars)
{
	t_env_list	*previous;
	t_env_list	*temp;
	char		**split;
	int			i;
	t_env_list	*head;

	previous = NULL;
	i = 0;
	split = ft_split(vars, 32);
	head = env_list;
	while (split[i])
	{
		env_list = head;
		while (env_list)
		{
			if (!ft_strncmp(env_list->name, split[i], ft_strlen(split[i]))
				&& ft_strlen(split[i]) == ft_strlen(env_list->name))
			{
				if (previous)
				{
					previous->next = env_list->next;
					free(env_list);
				}
				else
				{
					temp = env_list;
					env_list = env_list->next;
					free(temp);
				}
				break ;
			}
			previous = env_list;
			env_list = env_list->next;
		}
		i++;
	}
	free(split[0]);
	free(split[1]);
	free(split);
}
