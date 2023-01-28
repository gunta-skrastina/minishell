/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:39:05 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/28 16:40:11 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (!ft_strncmp(str, "-n ", 3)
		|| (!ft_strncmp(str, "-n", 2) && ft_strlen(str) == 2))
		i = 3;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			ft_putchar_fd(str[i], 1);
		else
		{
			quote = str[i++];
			while (str[i] != quote)
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
		}
		i++;
	}
	if (ft_strncmp(str, "-n ", 3)
		|| (ft_strncmp(str, "-n", 2) && ft_strlen(str) == 2))
		ft_putchar_fd('\n', 1);
}
