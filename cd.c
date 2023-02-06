/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:18:49 by gskrasti          #+#    #+#             */
/*   Updated: 2023/02/05 19:25:32 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	homeless(t_env_list *env_list, char *path, int i);

int	cd(char *path, t_env_list *env_list, t_cmd *cmd, int fd_out)
{
	int		i;
	char	*pwd;

	if (ft_in_validation(cmd, &fd_out, cmd->in) < 0)
		return (1);
	if (fd_out != STDIN_FILENO)
		close(fd_out);
	if (ft_out_validation(cmd, &fd_out) < 0)
		return (1);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	i = 0;
	if (!(ft_getenv("PWD", env_list)))
	{
		pwd = getcwd(NULL, 0);
		ft_env_lstadd_back(&env_list,
			ft_env_lstnew(ft_strjoin("PWD", ""), pwd));
	}
	if (path && path[0])
		i = replace_pwd(env_list, path);
	else
		i = homeless(env_list, path, i);
	if (i == -1)
		return (ft_error("cd", path, "No such file or directory"));
	return (0);
}

int	replace_pwd(t_env_list *env_list, char *path)
{
	char	*pwd;
	int		i;

	i = chdir(path);
	pwd = ft_getenv("PWD", env_list)->value;
	if (ft_getenv("OLDPWD", env_list))
	{
		free(ft_getenv("OLDPWD", env_list)->value);
		ft_getenv("OLDPWD", env_list)->value = pwd;
	}
	else
		ft_env_lstadd_back(&env_list,
			ft_env_lstnew(ft_strjoin("OLDPWD", ""), pwd));
	pwd = getcwd(NULL, 0);
	ft_getenv("PWD", env_list)->value = pwd;
	return (i);
}

static int	homeless(t_env_list *env_list, char *path, int i)
{
	if (ft_getenv("HOME", env_list))
	{
		path = ft_getenv("HOME", env_list)->value;
		i = replace_pwd(env_list, path);
	}
	else
		return (ft_error("cd", NULL, "HOME not set"));
	return (i);
}
