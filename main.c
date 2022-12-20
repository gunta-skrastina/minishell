/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:02:58 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/20 14:57:46 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (42)
	{
		str = readline("> ");
		if (ft_strlen(str) > 0)
			add_history(str);
		str = replace(str, -1);
		printf("%s\n", str);
	}
	return (0);
}
