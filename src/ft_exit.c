/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:11:09 by greed         #+#    #+#                 */
/*   Updated: 2020/10/27 12:04:58 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_arg_exit_val(t_cmd *cmd)
{
	int		i;
	int		ret;

	i = 0;
	if (cmd->argv[0][i] == '-')
		i++;
	while (cmd->argv[0][i] && ft_isdigit(cmd->argv[0][i]))
		i++;
	if (!cmd->argv[0][i])
	{
		ret = ft_atoi(cmd->argv[0]);
		ret = ret % 256;
	}
	else
	{
		ft_printf_fd(2, "Error: exit: numeric argument required\n");
		ret = 2;
	}
	return (ret);
}

void	ft_exit(t_cmd *cmd, int last_status)
{
	int		ret;

	if (g_signal_exit != 0)
		ret = g_signal_exit + 128;
	else
		ret = last_status;
	if (cmd->argv && cmd->argc == 1 && cmd->argv[0])
	{
		ret = get_arg_exit_val(cmd);
		if (ret == -1)
			ft_printf_fd(2, "Error: exit: invalid argument\n");
	}
	else if (cmd->argc > 1)
	{
		ft_printf_fd(2, "Error: exit: too many arguments\n");
		ret = 2;
	}
	exit(ret);
}
