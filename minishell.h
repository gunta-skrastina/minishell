/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:03:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/09 15:51:25 by gskrasti         ###   ########.fr       */
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

typedef struct s_env_list
{
	char				*name;
	char				*value;
	int					num;
	struct s_env_list	*next;
}					t_env_list;

char		*replace(char *str, int i, t_env_list *env_list);
char		*replace_env(char *str, int i, char quote, t_env_list *env_list);
int			ft_charcmp(const char *str, char c);
char		*ft_new_str(char *str, int i, int j, char *env, t_env_list *env_list);
void		handle_signals(int sig);
t_env_list	*ft_env_lstnew(char *name, char *value);
t_env_list	*ft_env_lstlast(t_env_list *lst);
void		ft_env_lstadd_back(t_env_list **lst, t_env_list *new);
int			ft_env_lstsize(t_env_list *lst);
t_env_list	*init_env_list(char **envp);
t_env_list	*ft_getenv(char *env, t_env_list *env_list);
void		env(t_env_list *env_list);
void		pwd(void);
void		unset(t_env_list *env_list, char *cmd);
void		export(t_env_list *env_list, char **var);
void		export_env(t_env_list *env_list, char *var);
void		cd(char *path);
void		ft_error(char *cmd, char *path, char *err);
void		echo(char *var, char flag);
char		**split_env(char const *s, char c);

#endif