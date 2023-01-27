/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:39:05 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/27 22:42:39 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "-n ", 3) || (!ft_strncmp(str, "-n", 2) && ft_strlen(str) == 2))
	{
		i = 3;
		while (str[i])
		{
			if (str[i] != '"' && str[i] != '\'')
				ft_putchar_fd(str[i], 1);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (str[i] != '"' && str[i] != '\'')
				ft_putchar_fd(str[i], 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
}
