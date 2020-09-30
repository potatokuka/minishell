/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 10:57:24 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/30 11:52:32 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_dispatch(t_fd_sto *fd, t_cmd *cmd, char *pipe)
{
	if (cmd && pipe)
	{
		dprintf(2, "pipe =%s\n", pipe);
		if (ft_strcmp(pipe, ">>") == 0)
			redir_append(fd, cmd);
		else if (ft_strcmp(pipe, "<") == 0)
			redir_std_input(fd, cmd);
		else if (ft_strcmp(pipe, ">") == 0)
			redir_trunc(fd, cmd);
	}
	return ;
}
