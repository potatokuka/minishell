/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 10:57:24 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/30 10:59:09 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_dispatch(t_cmd *cmd, char *pipe)
{
	if (cmd && pipe)
	{
		dprintf(2, "pipe =%s\n", pipe);
		if (ft_strcmp(pipe, ">>") == 0)
			redir_append(cmd);
		else if (ft_strcmp(pipe, "<") == 0)
			redir_std_input(cmd);
		else if (ft_strcmp(pipe, ">") == 0)
			redir_trunc(cmd);
	}
	return ;
}
