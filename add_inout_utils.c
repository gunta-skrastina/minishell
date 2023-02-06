/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inout_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:23:14 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/01 03:02:33 by htoustsi         ###   ########.fr       */
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
	return ;
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

int	ft_num_infiles(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->in && cmd->in[i])
		++i;
	return (i);
}
