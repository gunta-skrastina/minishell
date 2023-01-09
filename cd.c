/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:18:49 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/09 14:27:42 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path)
{
	int		i;

	i = 0;
	if (path)
	{
		i = chdir(path);
	}
	else
	{
		if (getenv("HOME"))
		{
			path = getenv("HOME");
			i = chdir(path);
		}
		else
			ft_error("cd", NULL, "HOME not set");
	}
	if (i == -1)
		ft_error("cd", path, "No such file or directory");
}
