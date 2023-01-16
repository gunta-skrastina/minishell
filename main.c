/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:02:58 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/16 14:09:25 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	char		*str;
	t_env_list	*env_list;
	t_cmd		*cmd;

	if (argc != 1 && argv)
	{
		printf("ERROR: No arguments required\n");
		exit(0);
	}
	env_list = init_env_list(envp);
	while (42 || env_list)
	{
		signal(SIGQUIT, SIG_IGN);
		// signal(SIGINT, handle_signals);
		str = readline("> ");
		if (ft_strlen(str) > 0)
			add_history(str);
		str = replace(str, -1, env_list);
		if (str)
		{
			if (str[ft_strlen(str) - 1] == '|' || str[0] == '|')
				printf("minishell: parse error near `|'\n");
			else if (validate_quotes(str) < 0)
				printf("minishell: parse error near quotes\n");
			else
			{
				cmd = parse(str);
				execute_builtins(cmd, env_list);
			}
		}
		free_cmd(cmd);
		free(str);
	}
	return (0);
}
