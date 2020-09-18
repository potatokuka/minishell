/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 18:43:45 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/18 13:34:38 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Iterate over argv and replace any enviroment variables with strings of
** their value
*/

void	subtitute_enviroment_variables(t_data *data)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i < data->argc)
	{
		if (data->argv[i][0] == '$' && ft_strlen(data->argv[i]) > 1)
		{
			ptr = &(data->argv[i][1]);
			ptr = get_env_val(ptr, data->env, ft_strlen(ptr));
			ptr = ft_strdup((ptr) ? ptr : "");
			free(data->argv[i]);
			data->argv[i] = ptr;
		}
		i++;
	}
}
