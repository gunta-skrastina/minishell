/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:46:26 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/15 02:00:19 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdnew(char *cmd, char *vars)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = cmd;
	new_cmd->vars = vars;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	if (*lst)
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*lst = new;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp_cmd;

	while (cmd)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		free(temp_cmd);
	}
}