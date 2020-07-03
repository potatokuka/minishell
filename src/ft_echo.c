/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/06/29 18:54:43 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (i < inp->cmd->argc)
	{
		if (inp->cmd->argv[i][0] == '<' || inp->cmd->argv[i][0] == '>')
		{
			printf("\n");
			return ;			
		}
		printf("%s", inp->cmd->argv[i]);
		if ((inp->cmd->argc - i) > 1)
			printf(" ");
		else
			printf("\n");
		i++;
	}
	return ;
}
