/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/10/01 13:40:39 by averheij      ########   odam.nl         */
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
	int flag;

	flag = 0;
	i = 0;
	if (cmd->argc != 0 && ft_strcmp(cmd->argv[0], "-n") == 0)
	{
		flag += 1;
		i++;
	}
	dprintf(2,"ECHO -------------\n");
	while (i < cmd->argc)
	{
		ft_printf_fd(1, "%s", cmd->argv[i]);
		if (cmd->argc - i == 1)
		{
			if (flag == 1)
				break ;
			ft_printf_fd(1, "\n");
		}
		else
			ft_printf_fd(1, " ");
		i++;
	}
	return ;
}
