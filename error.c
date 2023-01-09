/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:38:38 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/09 14:23:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *cmd, char *path, char *err)
{
	if (!path)
		printf("minishell: %s: %s\n", cmd, err);
	else
		printf("minishell: %s: %s: %s\n", cmd, path, err);
}
