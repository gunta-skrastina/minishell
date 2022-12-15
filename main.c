/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:02:58 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/15 13:30:13 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str;

	while (42)
	{
		str = readline("> ");
		if(ft_strlen(str) > 0)
			 add_history(str);
	}
	return (0);
}
