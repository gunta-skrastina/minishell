/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:45:20 by htoustsi          #+#    #+#             */
/*   Updated: 2023/02/05 20:40:46 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

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
	struct s_out	lim;
	char			**in;
	struct s_out	*out;
	struct s_cmd	*next;
}					t_cmd;

void		replace_tabs(char *str);
char		*replace(char *str, int i, t_env_list *env_list);
char		*replace_env(char *str, int i, t_env_list *env_list);
int			ft_charcmp(const char *str, char c);
char		*ft_new_str(char *str, char *env,
				char *end_str, t_env_list *env_list);
void		handle_signals(int sig);
t_env_list	*ft_env_lstnew(char *name, char *value);
t_env_list	*ft_env_lstlast(t_env_list *lst);
void		ft_env_lstadd_back(t_env_list **lst, t_env_list *new);
int			ft_env_lstsize(t_env_list *lst);
t_env_list	*init_env_list(char **envp);
t_env_list	*ft_getenv(char *env, t_env_list *env_list);
int			env(t_cmd *cmd, t_env_list *env_list, int fd_out, int proc);
int			pwd(t_cmd *cmd, int fd_out, int proc);
int			unset(t_env_list *env_list, char *vars, t_cmd *cmd, int fd_out);
int			export(t_cmd *cmd, t_env_list *env, char *vars, int proc);
void		export_env(t_env_list *env, char *var);
int			cd(char *path, t_env_list *env_list, t_cmd *cmd, int fd_out);
int			ft_error(char *cmd, char *path, char *err);
int			echo(t_cmd *cmd, int fd_out, int i);
char		**split_env(char const *s, char c);
int			replace_pwd(t_env_list *env_list, char *path);
int			execute_builtins(t_cmd *cmd, t_env_list *env_list);
t_cmd		*parse(char *str);
t_cmd		*ft_cmdnew(char *cmd, char *vars);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int			validate_quotes(char *str);
t_cmd		*parse_vars(t_cmd *cmd);
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
int			ft_charcmp_quotes(char *str, char c);
void		ft_free_split(char **s, int i);
size_t		ft_numwords(const char *s, char c);
int			ft_add_in(t_cmd *cmd, int cut_start, int pos_in);
int			ft_add_out(t_cmd *cmd, int cut_start, int pos_out);
void		ft_cut_filename(char **s, int pos, int num);
char		*ft_readline_fd(int fd, int ind);
void		ft_getline_cmd(int pip[2], char *limiter);
int			ft_in_validation(t_cmd *cmd, int *fd, char **infiles);
int			ft_out_validation(t_cmd *cmd, int *fd);
int			ft_parce_limcmd(t_cmd *cmd, char **argv, t_env_list *env,
				char **envp);
void		ft_pipe_new(t_cmd *cmd, t_env_list *env_list);
int			ft_redirect(t_cmd *cmd, char **argv);
int			ft_process_splitin(t_cmd *cmd, int *pos_in, int i,
				int cut_start);
int			ft_process_splitout(t_cmd *cmd, int *pos_out, int i,
				int cut_start);
int			ft_num_infiles(t_cmd *cmd);
char		*split_inout(char const *s);
int			handle_errno(t_cmd *cmd, int err);
int			find_multi_char(char *str, char c, int count);
int			handle_in(char *str);
char		**convert_env(t_env_list *env);
int			count_env(t_env_list *env);
int			ft_is_builtin(char *str);
int			ft_clone_inout(int fd, int standard);
void		ft_file_export(int size, t_env_list *env, t_cmd *cmd);
char		**split_argv(char *str);
int			ft_handle_filesonly(t_cmd *cmd);
void		ft_choose_exec(t_cmd *cmd, char **argv, char **envp,
				t_env_list *env);
int			ft_execute_fromlim(t_cmd *cmd, int pip1[2], char **argv,
				char **envp);
int			ft_collect_topipe(int pip1[2], t_cmd *cmd);
int			ft_out_validation(t_cmd *cmd, int *fd);
void		ft_first_pipe(t_cmd *cmd, t_env_list *env, int pip[2]);
void		ft_last_pipe(t_cmd *cmd, t_env_list *env, int pip[2]);
void		ft_middle_pipe(t_cmd *cmd, t_env_list *env, int pip[2],
				int pip2[2]);
t_cmd		*ft_execute_pipechain(t_cmd *cmd, t_env_list *env,
				int *fd_in, int *fd_out);
void		ft_lim_inchild(int pip[2], t_cmd *cmd);
int			check_if_valid_env(char *str);
void		ft_handle_unexisting(t_cmd *cmd);

#endif