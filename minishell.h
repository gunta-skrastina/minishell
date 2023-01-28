/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:03:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/28 18:07:54 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

int	g_err;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	int					num;
	struct s_env_list	*next;
}					t_env_list;

typedef struct s_out
{
	char	*name;
	int		num;
}			t_out;

typedef struct s_cmd
{
	char			*cmd;
	char			*vars;
	int				here_doc;
	char			*lim;
	char			**in;
	struct s_out	*out;
	struct s_cmd	*next;
}					t_cmd;

char		*replace(char *str, int i, t_env_list *env_list);
char		*replace_env(char *str, int i, t_env_list *env_list);
int			ft_charcmp(const char *str, char c);
char		*ft_new_str(char *str, char *env, char *end_str, t_env_list *env_list);
void		handle_signals(int sig);
t_env_list	*ft_env_lstnew(char *name, char *value);
t_env_list	*ft_env_lstlast(t_env_list *lst);
void		ft_env_lstadd_back(t_env_list **lst, t_env_list *new);
int			ft_env_lstsize(t_env_list *lst);
t_env_list	*init_env_list(char **envp);
t_env_list	*ft_getenv(char *env, t_env_list *env_list);
void		env(t_env_list *env_list);
void		pwd(void);
void		unset(t_env_list *env_list, char *vars);
void		export(t_env_list *env, char *vars);
void		export_env(t_env_list *env, char *var);
void		cd(char *path, t_env_list *env_list);
void		ft_error(char *cmd, char *path, char *err);
void		echo(char *vars);
char		**split_env(char const *s, char c);
int			replace_pwd(t_env_list *env_list, char *path);
int			execute_builtins(t_cmd *cmd, t_env_list *env_list);
t_cmd		*parse(char *str);
t_cmd		*ft_cmdnew(char *cmd, char *vars);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int			validate_quotes(char *str);
t_cmd		*parse_vars(t_cmd *cmd);
void		echo(char *str);
void		ft_exit(t_cmd *cmd, t_env_list *env);
void		remove_quotes(t_cmd *cmd);
char		*without_quotes(char *str);
void		free_cmd(t_cmd *cmd);
char		*remove_spaces(char *str);
void		free_env_list(t_env_list *env);
int			execute_path(t_cmd *cmd, t_env_list *env);
char		*find_path(char *cmd, t_env_list *env);
void		export_add(t_env_list *env, char *vars);
void		rl_replace_line(const char *text, int clear_undo);
char		*dollar_question(char *str, int i);


void		ft_free_split(char **s, int i);
size_t		ft_numwords(const char *s, char c);
int			ft_add_in(t_cmd *cmd);
int			ft_add_out(t_cmd *cmd);
void		ft_cut_filename(char **s, int pos, int num);

#endif