/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 10:57:24 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/21 17:30:53 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redir_dispatch(t_data *data, t_fd_sto *fd, t_cmd *cmd, char *pipe)
{
	if (cmd && pipe)
	{
		/*dprintf(2, "pipe =%s\n", pipe);*/
		if (ft_strcmp(pipe, ">>") == 0)
		{
			if (redir_append(data, fd, cmd))
				return (1);
		}
		else if (ft_strcmp(pipe, "<") == 0)
		{
			if (redir_std_input(data, fd, cmd))
				return (1);
		}
		else if (ft_strcmp(pipe, ">") == 0)
			if (redir_trunc(data, fd, cmd))
				return (1);
	}
	return (0);
}
