/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:14:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/14 02:41:21 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	cmd = ft_cmdnew(str, NULL);
	while (i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += ft_charcmp(str + i + 1, str[i]) + 1;
		}
		else if (str[i] == '|')
		{
			str[i] = '\0';
			ft_cmdadd_back(&cmd, ft_cmdnew(str + i + 1, NULL));
		}
		i++;
	}
	cmd = parse_vars(cmd);
	return (cmd);
}

t_cmd	*parse_vars(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	temp = cmd;
	while (temp && temp->cmd)
	{
		i = 0;
		while (temp->cmd[i] && temp->cmd[i] != 32)
		{
			i++;
		}
		if (temp->cmd + i + 1)
		{
			temp->vars = temp->cmd + i + 1;
		}
		else
		{
			temp->vars = ft_calloc(1, sizeof(char *));
		}
		temp->cmd[i] = '\0';
		temp = temp->next;
	}
	return (cmd);
}

int	validate_quotes(char *str)
{
	int		i;
	int		c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = ft_charcmp(str + i + 1, str[i]);
			if (c < 0)
				return (c);
			else
				i += c + 1;
		}
		i++;
	}
	return (0);
}
