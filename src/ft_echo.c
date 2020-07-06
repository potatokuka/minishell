/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 13:14:13 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** while argc is > 1 print ' ' when argc == 1 print '\n'
** start printing from lowest argc to highest to get correct order
** make a counter i starting at 0
*/

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("ECHO -------------\n");
	while (i < cmd->argc)
	{
		ft_printf_fd(1, "%s", cmd->argv[i]);
		if ((cmd->argc - i) > 1)
			ft_printf_fd(1, " ");
		else
			ft_printf_fd(1, "\n");
		i++;
	}
	return ;
}
