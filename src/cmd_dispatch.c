/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/06/19 18:05:41 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_dispatch(t_input *inp)
{
	if (ft_strncmp(inp->cmd, "exit", 4) == 0)
		ft_exit(inp);
	else if (ft_strncmp(inp->cmd, "echo", 4) == 0)
		ft_echo(inp);
	/* else if (ft_strncmp(inp->cmd, "env", 3) == 0) */
	/* 	ft_env(inp); */
	/* else if (ft_strncmp(inp->cmd, "pwd", 3) == 0) */
	/* 	ft_pwd(inp); */
	else
		return ;
}
