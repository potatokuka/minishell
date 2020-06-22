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

void	print_env(t_input *inp, char *str, int i)
{
	char	*name;
	char	*to_print;
	int		len;

	/* this should move the pointer off of the '$' */
	str += 1;
	name = ft_strdup(str);
	len = ft_strlen(name);
	to_print = get_env_val(name, inp->env, len);
	printf("TO PRINT =_%s\n", to_print);
	if (!to_print)
	{
		/* it doesnt like this at all */
		ft_printf_fd(2, "echo: %s not set\n", name);
		return ;
	}
	else
	{
		printf("ENV ECHO_%s_", to_print);
		if (inp->argc > 1 && inp->argv[i + 1] && 
					inp->argv[i + 1][0] != '$')
			printf(" ");
		else if (inp->argc < 1)
			printf("\n");
		else
			return ;
	}
	return ;
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
		/* printf("%s\n", inp->argv[i]); */
		if (inp->argv[i][0] == '$')
		{
			print_env(inp, inp->argv[i], i);
			i += 1;
			inp->argc -= 1;
			if (inp->argc < 1)
				break ;
		}
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
