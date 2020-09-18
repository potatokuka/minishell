/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 18:43:45 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/18 17:44:30 by averheij      ########   odam.nl         */
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

char	*replace(t_data *data, char *str, int dollerdex)
{
	int		end;
	char	*envvar;
	char	*res;

	str[dollerdex] = '\0';
	envvar = str + dollerdex + 1;
	end = 0;
	while (envvar[end] && ft_env_char(envvar[end]))
		end++;
	if (end > 1)
	{
		envvar = get_env_val(envvar, data->env, end);
		envvar = ft_strdup((envvar) ? envvar : "");
		res = ft_3strjoin(str, envvar, str + dollerdex + 1 + end);
		free(str);
		free(envvar);
		str = res;
	}
	return (str);
}

void	subtitute_enviroment_variables(t_data *data)
{
	int		i;
	int		u;
	char	*ptr;

	i = 0;
	while (i < data->argc)
	{
		u = 0;
		while (data->argv[i] && data->argv[i][u])
		{
			if (data->argv[i][u] == '$')
				data->argv[i] = replace(data, data->argv[i], u);
			u++;
		}
		ft_printf_fd(2, "arg%d:%s\n", i, data->argv[i]);
		i++;
	}
}
