/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:35:40 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/18 18:21:30 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_charcmp(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}
