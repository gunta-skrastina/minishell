/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:39:05 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 01:56:50 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char *str, int i, int fd_out);
static int	str_start(char *str, int i);
static int	count_n(char *str, int i);

int	echo(t_cmd *cmd, int fd_out, int i)
{
	char	*str;

	str = cmd->vars;
	if (ft_in_validation(cmd, &fd_out, cmd->in) < 0)
		return (1);
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	if (ft_out_validation(cmd, &fd_out) < 0)
		return (1);
	if (!str)
	{
		ft_putchar_fd('\n', fd_out);
		return (0);
	}
	i = 0;
	while (str[i] == 32)
		i++;
	i = str_start(str, i);
	print_echo(str, i, fd_out);
	return (0);
}

static void	print_echo(char *str, int i, int fd_out)
{
	char	quote;

	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			ft_putchar_fd(str[i], fd_out);
		else
		{
			quote = str[i++];
			while (str[i] != quote)
			{
				ft_putchar_fd(str[i], fd_out);
				i++;
			}
		}
		i++;
	}
	if (ft_strncmp(str, "-n ", 3) && ft_strncmp(str, "-n\0", 3)
		&& ft_strncmp(str, "\"-n\" ", 5) && ft_strncmp(str, "\"-n\"\0", 5)
		&& ft_strncmp(str, "'-n' ", 5)
		&& ft_strncmp(str, "'-n\'0", 5) && !count_n(str, 0))
		ft_putchar_fd('\n', fd_out);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}

static int	str_start(char *str, int i)
{
	int	j;

	while (42)
	{
		if (!ft_strncmp(str + i, "-n ", 3) || !ft_strncmp(str + i, "-n\0", 3))
			i += 3;
		else if (!ft_strncmp(str + i, "\"-n\" ", 5)
			|| !ft_strncmp(str + i, "\"-n\"\0", 5)
			|| !ft_strncmp(str + i, "'-n' ", 5)
			|| !ft_strncmp(str + i, "'-n'\0", 5))
			i += 5;
		else if (!ft_strncmp(str + i, "-nn", 3)
			|| !ft_strncmp(str + i, "\"-nn", 4)
			|| !ft_strncmp(str + i, "\'-nn", 4))
		{
			j = count_n(str, i);
			if (j > i)
				i = j;
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

static int	count_n(char *str, int i)
{
	int		j;
	char	quote;

	j = i;
	if (!ft_strncmp(str + i, "'-n", 3) || !ft_strncmp(str + i, "\"-n", 3))
	{
		quote = str[j];
		j += 3;
		while (str[j] == 'n')
			j++;
		if (str[j] == quote && (str[j + 1] == '\0' || str[j + 1] == 32))
			i = j + 2;
	}
	else if (str[j] == '-')
	{
		j++;
		while (str[j] == 'n')
			j++;
		if (str[j] == '\0' || str[j] == 32)
			i = j + 1;
	}
	return (i);
}
