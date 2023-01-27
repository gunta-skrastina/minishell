/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:46:46 by htoustsi          #+#    #+#             */
/*   Updated: 2023/01/28 00:42:27 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **s, int i)
{
	while (s[i])
	{
		free(s[i]);
		++i;
	}
	free(s);
}

size_t	ft_numwords(const char *s, char c)
{
	size_t	nwords;
	size_t	count;

	nwords = 0;
	count = 0;
	while ((s[count]) && (s[count] != '\0') && (s[count] != '\n'))
	{
		if ((s[count] != c) && ((s[count + 1] == '\0')
				|| (s[count + 1] == c) || (s[count + 1] == '\n')))
			++nwords;
		++count;
	}
	return (nwords);
}

void	ft_cut_filename(char **s, int pos, int num)
{
	while ((*s)[pos] && (*s)[pos + num] && (*s)[pos] != '\0' && (*s)[pos + num] != '\0')
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

int	ft_add_in(t_cmd *cmd)
{
	int		i;
	int		len;
	int		cut_start;
	int		pos_in;
	char	**temp;

	while (cmd && cmd->cmd)
	{
		len = ft_numwords(cmd->cmd, '<');
		cmd->in = (char **)malloc(sizeof(char *) * len);
		if (!cmd->in)
			return (0);
		pos_in = 0;
		cmd->here_doc = 0;
		i = ft_charcmp(cmd->cmd, '<');
		while (i != -1)
		{
			cut_start = i;
			if (cmd->cmd[i + 1] == '<')
			{
				cmd->here_doc = 1;
				//cut out the limiter and store it
				i = i + 2;
			}
			else
			{
				while (cmd->cmd[i + 1] == ' ')
					++i;
				temp = ft_split(&(cmd->cmd[i + 1]), ' ');
				cmd->in[pos_in] = temp[0];
				if (!temp[1])
					free(temp);
				else
					ft_free_split(temp, 1);
				ft_cut_filename(&(cmd->cmd), cut_start, i + 1 + ft_strlen(cmd->in[pos_in]) - cut_start);
				printf("cut in result: %s; %s\n", cmd->cmd, cmd->in[0]);
				++pos_in;
			}
			i = ft_charcmp(&(cmd->cmd[i]), '<');
		}
		cmd = cmd->next;
	}
	return (1);
}

int	ft_add_out(t_cmd *cmd)
{
	int		i;
	int		len;
	int		cut_start;
	int		pos_out;
	char	**temp;

	while (cmd && cmd->cmd)
	{
		len = ft_numwords(cmd->cmd, '>');
		cmd->out = (t_out *)malloc(sizeof(t_out) * len);
		if (!cmd->out)
			return (0);
		pos_out = 0;
		i = ft_charcmp(cmd->cmd, '>');
		while (i != -1)
		{
			cut_start = i;
			cmd->out->num = 0;
			if (cmd->cmd[i + 1] == '>')
			{
				cmd->out->num = 1;
				++i;
			}
			while (cmd->cmd[i + 1] == ' ')
					++i;
			temp = ft_split(&(cmd->cmd[i + 1]), ' ');
			(cmd->out[pos_out]).name = temp[0];
			if (temp[1])
				ft_free_split(temp, 1);
			else
				free(temp);
			ft_cut_filename(&(cmd->cmd), cut_start - cmd->out->num, i + 1 + ft_strlen(cmd->out[pos_out].name) - cut_start);
			printf("cut out result: %s; %s\n", cmd->cmd, cmd->out[0].name);
			++pos_out;
			++i;
			i = ft_charcmp(&(cmd->cmd[i]), '>');
		}
		cmd = cmd->next;
	}
	return (1);
}
