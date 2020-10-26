/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/10/26 17:41:36 by averheij      ########   odam.nl         */
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
	while (i < cmd->argc)
	{
		if (ft_strcmp(cmd->argv[i], "-n") == 0 && flag == i)
			flag += 1;
		else
		{
			ft_printf_fd(1, "%s", cmd->argv[i]);
			if (cmd->argc - i == 1)
			{
				if (flag >= 1)
					break ;
				ft_printf_fd(1, "\n");
			}
			else
				ft_printf_fd(1, " ");
		}
		i++;
	}
}
