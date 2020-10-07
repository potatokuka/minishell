/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 18:43:45 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/07 10:17:52 by greed         ########   odam.nl         */
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

bool	ft_env_char(int c, int first)
{
	bool	yes_question_mark;

	yes_question_mark = 0;
	if (first && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'))
		yes_question_mark = 1;
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9'))
		yes_question_mark = 1;
	return (yes_question_mark);
}

char	*str_env_replace_index(t_data *data, char *str, int envstart)
{
	int		envend;
	char	*envvar;
	char	*res;

	str[envstart] = '\0';
	envvar = str + envstart + 1;
	envend = 0;
	while (envvar[envend] && ft_env_char(envvar[envend], (envend == 0) ? 1 : 0))
		envend++;
	if (envend == 0 && *envvar == '?')
		envend = 1;
	if (envend >= 1)
	{
		envvar = get_env_val(envvar, data->env, envend);
		envvar = ft_strdup((envvar) ? envvar : "");// freed LINE 58
		res = ft_3strjoin(str, envvar, str + envstart + 1 + envend);//Protection
		if (!res)
			put_error("Allocation error");
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
		if (str[i] == '$' && check_escape(str, i))
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
