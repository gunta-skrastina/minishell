/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:14:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 14:48:56 by gskrasti         ###   ########.fr       */
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
	remove_quotes(cmd);
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

void	remove_quotes(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->cmd = remove_spaces(cmd->cmd);
		cmd->cmd = without_quotes(cmd->cmd);
		if (cmd->vars)
		{
			cmd->vars = remove_spaces(cmd->vars);
			if (ft_strncmp(cmd->cmd, "echo", 4))
				cmd->vars = without_quotes(cmd->vars);
		}
		cmd = cmd->next;
	}
}

char	*without_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			k = ft_charcmp(str + i + 1, str[i]) + i ;
			i++;
			while (i <= k)
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	free(str);
	return (new_str);
}