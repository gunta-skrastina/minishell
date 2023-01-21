/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:18:49 by gskrasti          #+#    #+#             */
/*   Updated: 2023/01/15 15:10:23 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path, t_env_list *env_list)
{
	int		i;
	char	*pwd;

	i = 0;
	if (!(ft_getenv("PWD", env_list)))
	{
		pwd = getcwd(NULL, 0);
		ft_env_lstadd_back(&env_list, ft_env_lstnew("PWD", pwd));
	}
	if (path && path[0])
	{
		i = chdir(path);
		replace_pwd(env_list);
	}
	else
	{
		if (ft_getenv("HOME", env_list))
		{
			path = ft_getenv("HOME", env_list)->value;
			i = chdir(path);
			replace_pwd(env_list);
		}
		else
			ft_error("cd", NULL, "HOME not set");
	}
	if (i == -1)
		ft_error("cd", path, "No such file or directory");
}

void	replace_pwd(t_env_list *env_list)
{
	char	*pwd;

	pwd = ft_getenv("PWD", env_list)->value;
	free(ft_getenv("OLDPWD", env_list)->value);
	ft_getenv("OLDPWD", env_list)->value = pwd;
	pwd = getcwd(NULL, 0);
	ft_getenv("PWD", env_list)->value = pwd;
}