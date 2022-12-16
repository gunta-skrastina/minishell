/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:17:42 by gskrasti          #+#    #+#             */
/*   Updated: 2022/12/16 21:10:03 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace(char *str, int i)
{
	char	quote;

	while (str[++i])
	{	
		if (str[i] == '$')
			replace_env(str, i, '\0');
		else if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			if ((ft_charcmp(str + i, quote)) >= 0)
			{
				printf("test\n");
				while (str[i] && str[i] != quote)
				{
					if (str[i] == '$' && quote == '"')
						str = replace_env(str, i, quote);
					i++;
				}
				replace(str, i);
			}
			else if (str[i + 1] && next_quote(str + i))
			{
				replace(str, i);
				printf("%s\n", str);
			}
		}
	}
}

//placeholder
char	*replace_env(char *str, int i, char c)
{
	if (!env_exists(str))
	{
		if (c == '\0')
		{
			str[i] = '&';
		}
		// else if (c == '\'')
		// {
			
		// }
		// else if (c == '"')
		// {
			
		// }
	}
	else
	{
		str[i] = '&';
	}
	str[i] = '#';
	return (str);
}

char	*env_exists(char *str)
{
	if (str)
		return (NULL);
	return (NULL);
}

char	next_quote(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (str[i]);
	}
	return ('\0');
}