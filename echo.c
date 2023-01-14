/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:39:05 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/13 22:52:05 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "-n ", 3))
	{
		while (str[i])
		{
			if (str[i] != '"' && str[i] != '\'')
				ft_putchar_fd(str[i], 1);
			i++;
		}
		ft_putchar_fd('\n', 1);
	}
	else
	{
		i = 3;
		while (str[i])
		{
			if (str[i] != '"' && str[i] != '\'')
				ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}
