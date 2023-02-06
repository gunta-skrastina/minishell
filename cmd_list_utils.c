/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:46:26 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/02 23:33:30 by htoustsi         ###   ########.fr       */
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
	new_cmd->here_doc = 0;
	new_cmd->lim.name = NULL;
	new_cmd->lim.num = -2;
	new_cmd->vars = NULL;
	new_cmd->in = NULL;
	new_cmd->out = NULL;
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
	int		i;

	while (cmd)
	{
		temp_cmd = cmd;
		cmd = cmd->next;
		free(temp_cmd->cmd);
		free(temp_cmd->vars);
		if (temp_cmd->lim.name != NULL)
			free(temp_cmd->lim.name);
		if (temp_cmd->in != NULL)
			ft_free_split(temp_cmd->in, 0);
		if (temp_cmd->out != NULL)
		{
			i = 0;
			while (temp_cmd->out[i].name)
			{
				free(temp_cmd->out[i].name);
				i++;
			}
			free(temp_cmd->out);
		}
		free(temp_cmd);
	}
}
