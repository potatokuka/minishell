/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 18:43:45 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/22 15:01:05 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Iterate over argv and replace any enviroment variables with strings of
** their value
*/

//Search through string till $, this is pre-env-string
//continue until end of arg or invalid char (check with ft_env_char), this is env var
//anything afterward is post-env-string
//	try to get env val based on var
//	3strjoin pre, env-val, post

int		ft_env_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

char	*str_env_replace_index(t_data *data, char *str, int envstart)
{
	int		envend;
	char	*envvar;
	char	*res;

	str[envstart] = '\0';
	envvar = str + envstart + 1;
	envend = 0;
	while (envvar[envend] && ft_env_char(envvar[envend]))
		envend++;
	if (envend > 1)
	{
		envvar = get_env_val(envvar, data->env, envend);
		envvar = ft_strdup((envvar) ? envvar : "");
		res = ft_3strjoin(str, envvar, str + envstart + 1 + envend);
		if (str)
			free(str);
		free(envvar);
		str = res;
	}
	return (str);
}

char	*str_env_replace(t_data *data, char *str, int all)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str = str_env_replace_index(data, str, i);
			if (!all)
				break;
		}
		i++;
	}
	return (str);
}

void	argv_env_replace(t_data *data)
{
	int		i;
	int		u;
	char	*ptr;

	i = 0;
	while (i < data->argc)
	{
		str_env_replace(data, data->argv[i], 1);
		i++;
	}
}
