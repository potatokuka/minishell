/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 13:43:46 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 13:51:37 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** send each argv to get removed from ENV if they exist 
*/

void		ft_unset(t_cmd *cmd, t_var **env)
{
	int		i;

	if (cmd->argc < 1)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		unset_env(env, cmd->argv[i]);
		i++;
	}
	cmd->update_env = 1;
}
