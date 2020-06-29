/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 18:43:45 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/29 18:57:51 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Iterate over argv and replace any enviroment variables with strings of
** their value
*/

void	repl_env_vars(t_input *inp)
{
	int		i;
	char	*ptr;

	i = 0;
	printf("repl env vars\n");
	while (i < inp->argc)
	{
		printf("\t%s ", inp->argv[i]);
		if (inp->argv[i][0] == '$' && ft_strlen(inp->argv[i]) > 1)
		{
			ptr = &(inp->argv[i][1]);
			ptr = get_env_val(ptr, inp->env, ft_strlen(ptr));
			ptr = ft_strdup((ptr) ? ptr : "");
			printf("val:%s", ptr);
			free(inp->argv[i]);
			inp->argv[i] = ptr;
		}
		printf("\n");
		i++;
	}
}
