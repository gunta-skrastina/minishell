/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:07:56 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/04 16:23:16 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_multi_char(char *str, char c, int count)
{
	int	i;
	int	j;

	i = ft_charcmp_quotes(str, c);
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i] == c)
		{			
			j++;
			i++;
		}
		if (j >= count)
			return (1);
		i++;
	}
	return (0);
}
