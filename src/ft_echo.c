/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 10:43:59 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** take Argv input the name is the next point on the string until it's ended
** then send this to get_env_val
*/

char	*print_env(t_input *inp, char *str)
{
	char	*name;
	char	*to_print;
	int		len;

	/* this should move the pointer off of the '$' */
	str += 1;
	name = ft_strdup(str);
	len = ft_strlen(name);
	to_print = get_env_val(name, inp->env, len);
	if (!to_print)
	{
		ft_printf_fd(2, "echo: %s not set\n", name);
		return (NULL);
	}
	else
		return (to_print);
}

/*
** while argc is > 1 print ' ' when argc == 1 print '\n'
** start printing from lowest argc to highest to get correct order
** make a counter i starting at 0
*/

void	ft_echo(t_input *inp)
{
	int	i;

	i = 0;
	printf("ECHO -------------\n");
	while (inp->argc > 0)
	{
		printf("%s\n", inp->argv[i]);
		if (inp->argv[i][0] == '$')
			inp->argv[i] = print_env(inp, inp->argv[i]);
		else if (inp->argc > 1)
		{
			printf(" ");
			i += 1;
			inp->argc -= 1;
		}
		else
		{
			perror("inside");
			printf("\n");
			return ;
		}
	}
	return ;
}
