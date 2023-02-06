/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:46:46 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/04 18:54:18 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cut_filename(char **s, int pos, int num)
{
	while ((*s)[pos] && (*s)[pos + num]
		&& (*s)[pos] != '\0' && (*s)[pos + num] != '\0')
	{
		(*s)[pos] = (*s)[pos + num];
		++pos;
	}
	if ((*s)[pos + num] == '\0')
	{
		while ((*s)[pos])
		{
			(*s)[pos] = '\0';
			++pos;
		}
	}
	return ;
}

int	ft_process_splitin(t_cmd *cmd, int *pos_in, int i, int cut_start)
{
	char	*temp;
	int		len;

	while (cmd->cmd[i + 1] == ' ')
		++i;
	temp = split_inout(&(cmd->cmd[i + 1]));
	len = ft_strlen(temp);
	if (pos_in == NULL)
	{
		cmd->lim.name = temp;
		cmd->lim.num = ft_num_infiles(cmd) - 1;
	}
	else
	{
		cmd->in[*pos_in] = temp;
		*pos_in = *pos_in + 1;
	}
	ft_cut_filename(&(cmd->cmd), cut_start,
		i + 1 + len - cut_start);
	return (i);
}

int	ft_process_splitout(t_cmd *cmd, int *pos_out, int i, int cut_start)
{
	int		len;

	while (cmd->cmd[i + 1] == ' ')
		++i;
	cmd->out[*pos_out].name = split_inout(&(cmd->cmd[i + 1]));
	len = ft_strlen(cmd->out[*pos_out].name);
	ft_cut_filename(&(cmd->cmd), cut_start - (cmd->out[*pos_out]).num,
		i + 1 + (cmd->out[*pos_out]).num + len - cut_start);
	*pos_out = (*pos_out) + 1;
	return (i);
}

int	ft_add_in(t_cmd *cmd, int cut_start, int pos_in)
{
	int	i;

	while (cmd && cmd->cmd)
	{
		cmd->in = ft_calloc(ft_numwords(cmd->cmd, '<') + 1, sizeof(t_out));
		if (!cmd->in)
			return (0);
		cmd->here_doc = 0;
		pos_in = 0;
		i = ft_charcmp_quotes(cmd->cmd, '<');
		while (i != -1)
		{
			cut_start = i;
			if (cmd->cmd[i + 1] == '<')
			{
				cmd->here_doc = 1;
				i = ft_process_splitin(cmd, NULL, i + 1, cut_start) + 2;
			}
			else
				i = ft_process_splitin(cmd, &pos_in, i, cut_start);
			i = ft_charcmp_quotes(cmd->cmd, '<');
		}
		cmd = cmd->next;
	}
	return (1);
}

int	ft_add_out(t_cmd *cmd, int cut_start, int pos_out)
{
	int	i;

	while (cmd && cmd->cmd)
	{
		cmd->out = ft_calloc(ft_numwords(cmd->cmd, '>') * 3, sizeof(t_out *));
		if (!cmd->out)
			return (0);
		pos_out = 0;
		i = ft_charcmp_quotes(cmd->cmd, '>');
		while (i != -1)
		{
			cut_start = i;
			cmd->out[pos_out].num = 0;
			if (cmd->cmd[i + 1] == '>')
			{
				cmd->out[pos_out].num = 1;
				cut_start += 1;
				++i;
			}
			i = ft_process_splitout(cmd, &pos_out, i, cut_start) + 1;
			i = ft_charcmp_quotes(cmd->cmd, '>');
		}
		cmd = cmd->next;
	}
	return (1);
}
