/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:17:20 by greed         #+#    #+#                 */
/*   Updated: 2020/11/03 14:01:16 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** while argc is > 1 print ' ' when argc == 1 print '\n'
** start printing from lowest argc to highest to get correct order
** make a counter i starting at 0
*/

int		dash_nn(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str && *str == 'n')
		str++;
	if (*str)
		return (0);
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int flag;

	flag = 0;
	i = 0;
	while (i < cmd->argc)
	{
		if (dash_nn(cmd->argv[i]) && flag == i)
			flag += 1;
		else
		{
			ft_printf_fd(1, "%s", cmd->argv[i]);
			/*if (cmd->argc - i == 1)*/
			/*{*/
				/*if (flag >= 1)*/
					/*break ;*/
				/*ft_printf_fd(1, "\n");*/
			/*}*/
			/*else*/
				/*ft_printf_fd(1, " ");*/
			if (cmd->argc - i != 1)
				ft_printf_fd(1, " ");
		}
		i++;
	}
	if (flag == 0)
		ft_printf_fd(1, "\n");
}
