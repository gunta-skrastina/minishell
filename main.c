/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:02:58 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 21:13:42 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *str);
static void	start_parse(char *str, t_env_list *env);

int	main(int argc, char *argv[], char **envp)
{
	char		*str;
	t_env_list	*env_list;

	if (argc != 1 && argv)
		exit(printf("ERROR: No arguments required\n"));
	env_list = init_env_list(envp);
	while (42)
	{
		signal(SIGQUIT, handle_signals);
		signal(SIGINT, handle_signals);
		str = readline("mini> ");
		if (!str)
		{
			free(str);
			free_env_list(env_list);
			exit(0);
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		if (check_syntax(str) == 0)
			start_parse(str, env_list);
	}
	return (0);
}

static int	check_syntax(char *str)
{
	int		ret;

	ret = 258;
	if (str[ft_strlen(str) - 1] == '|' || ft_charcmp_quotes(str, '|') == 0
		|| find_multi_char(str, '|', 3))
		printf("minishell: syntax error near unexpected token`|'\n");
	else if (validate_quotes(str) < 0)
		printf("minishell: syntax error unclosed quotes\n");
	else if (str[ft_strlen(str) - 1] == '<' || str[ft_strlen(str) - 1] == '>')
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (find_multi_char(str, '<', 3))
		printf("minishell: syntax error near unexpected token `<'\n");
	else if (find_multi_char(str, '>', 3))
		printf("minishell: syntax error near unexpected token `>\n'");
	else
		ret = 0;
	if (ret != 0)
	{
		g_err = ret;
		free(str);
	}
	return (ret);
}

static	void	start_parse(char *str, t_env_list *env)
{
	t_cmd		*cmd;
	char		*temp;

	replace_tabs(str);
	temp = str;
	str = remove_spaces(str);
	free(temp);
	if (check_syntax(str) != 0)
		return ;
	str = replace(str, -1, env);
	if (str)
	{
		cmd = parse(str);
		if (cmd->next == NULL)
			execute_builtins(cmd, env);
		else
			ft_pipe_new(cmd, env);
		if (cmd != NULL)
			free_cmd(cmd);
	}
	free(str);
}
