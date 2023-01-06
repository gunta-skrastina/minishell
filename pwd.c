/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:02:51 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/06 19:10:52 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_env_list *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->name, "PWD", 3)
			&& ft_strlen(env_list->name) == 3)
			printf("%s\n", env_list->value);
		else
			env_list = env_list->next;
	}
}
