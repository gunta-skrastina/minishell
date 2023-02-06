/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:34:24 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/04 20:11:13 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_in_validation(t_cmd *cmd, int *fd, char **infiles)
{
	int	i;

	i = 0;
	if ((cmd->here_doc) || (!cmd->in || !cmd->in[0]))
		*fd = STDIN_FILENO;
	else
	{
		while (cmd->in[i])
		{
			if (access(infiles[i], R_OK) < 0)
			{
				perror(cmd->in[i]);
				return (-1);
			}
			++i;
		}
		*fd = open(infiles[i - 1], O_RDONLY);
		if (*fd < 0)
		{
			perror("Input file");
			return (-1);
		}
	}
	return (1);
}

int	ft_open_outfile(t_cmd *cmd, int *fd, int i)
{
	if (cmd->out[i].num == 0)
		*fd = open(cmd->out[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (cmd->out[i].num == 1)
		*fd = open(cmd->out[i].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (*fd < 0)
	{
		perror("Output file");
		return (0);
	}
	return (1);
}

int	ft_out_validation(t_cmd *cmd, int *fd)
{
	int	i;

	i = 0;
	if (cmd->out && cmd->out[0].name)
	{
		while (cmd->out[i].name)
		{
			if (!ft_open_outfile(cmd, fd, i))
				return (-1);
			close(*fd);
			++i;
		}
		if (!ft_open_outfile(cmd, fd, i - 1))
			return (-1);
	}
	else
		*fd = STDOUT_FILENO;
	return (1);
}

int	ft_clone_inout(int fd, int standard)
{
	if ((fd != standard) && (dup2(fd, standard) < 0))
	{
		perror("Duplication stdin/stdout error");
		return (0);
	}
	return (1);
}
