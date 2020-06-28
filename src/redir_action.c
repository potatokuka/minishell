/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 13:36:22 by greed         #+#    #+#                 */
/*   Updated: 2020/06/28 13:36:27 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** check if CMD triggered, if it is not then just run the REDIR normal
** if if not run check the cmd, and then put into the directed file
** **** TAKE FROM HERE >> MOVE TO HERE ****
*/

/*
** check to see what kind of flag is given, direct to correct function 
*/

void	redir_dispatch(t_input *inp)
{
	int		i;

	i = 0;
	if (ft_strncmp(inp->redirs[i], ">>", 2))
		redir_append(inp);
	else if (ft_strncmp(inp->redirs[i], "<", 1))
		redir_std_input(inp);
	else if (ft_strncmp(inp->redirs[i], ">", 1))
		redir_std_out(inp);
}
