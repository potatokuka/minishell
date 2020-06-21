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

char	*print_env(t_input *inp)
{
	char	*name;
	
	i = 1;

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
		printf("%s", inp->argv[i]);
		if (inp->argc > 1)
		{
			printf(" ");
			i += 1;
			inp->argc -= 1;
		}
		else
		{
			printf("\n");
			return ;
		}
	}
	return ;
}
