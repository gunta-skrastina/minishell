/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:11:56 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 13:20:12 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_export(int size, t_env_list *env, t_cmd *cmd)
{
	int			i;
	int			fd_out;
	t_env_list	*head;

	i = 1;
	head = env;
	if (ft_out_validation(cmd, &fd_out) < 0)
		return ;
	if (ft_clone_inout(fd_out, STDOUT_FILENO))
	{
		while (size >= i)
		{
			if (env->num == i)
			{
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
				i++;
			}
			env = env->next;
			if (env == NULL)
				env = head;
		}
	}
	if (fd_out != STDOUT_FILENO)
		close (fd_out);
	exit(0);
}

int	check_if_valid_env(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i != 0 && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else
			return (-1);
	}
	return (0);
}
