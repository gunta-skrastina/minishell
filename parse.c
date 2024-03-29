/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:14:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 13:17:04 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	cmd = ft_cmdnew(str, NULL);
	while (i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
			i += ft_charcmp(str + i + 1, str[i]) + 1;
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
		if (ft_charcmp_quotes(temp->cmd, '<') != -1)
			g_err = ft_add_in(temp, 0, 0);
		if (ft_charcmp_quotes(temp->cmd, '>') != -1)
			g_err = ft_add_out(temp, 0, 0);
		i = 0;
		while (temp->cmd[i] == 32)
			i++;
		while (temp->cmd[i] && temp->cmd[i] != 32)
		{
			if (temp->cmd[i] == '"' || temp->cmd[i] == '\'')
				i += ft_charcmp(temp->cmd + i + 1, temp->cmd[i]) + 1;
			i++;
		}
		if (temp->cmd[i] != '\0')
			temp->vars = temp->cmd + i + 1;
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
	int	i;

	while (cmd)
	{
		cmd->cmd = remove_spaces(cmd->cmd);
		cmd->cmd = without_quotes(cmd->cmd);
		if (cmd->lim.name)
			cmd->lim.name = without_quotes(cmd->lim.name);
		i = -1;
		while (cmd->in && cmd->in[++i])
			cmd->in[i] = without_quotes(cmd->in[i]);
		i = -1;
		while (cmd->out && cmd->out[++i].name)
			cmd->out[i].name = without_quotes(cmd->out[i].name);
		if (cmd->lim.name)
			cmd->lim.name = without_quotes(cmd->lim.name);
		if (cmd->vars)
		{
			cmd->vars = remove_spaces(cmd->vars);
			if (ft_strncmp(cmd->cmd, "echo", 4) && (ft_strncmp(cmd->cmd,
						"export", 6)) && ft_is_builtin(cmd->cmd))
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
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	free(str);
	return (new_str);
}
