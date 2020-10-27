/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 13:43:46 by greed         #+#    #+#                 */
/*   Updated: 2020/10/27 11:38:44 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** send each argv to get removed from ENV if they exist
*/

int		ft_unset(t_cmd *cmd, t_var **env)
{
	int		i;
	int		ret;

	ret = 0;
	if (cmd->argc < 1)
		return (0);
	i = 0;
	while (cmd->argv[i])
	{
		ret = unset_env(env, cmd->argv[i]);
		if (ret)
			ft_printf_fd(2, "Error: unset: '%s' is invalid\n", cmd->argv[i]);
		i++;
	}
	cmd->update_env = 1;
	return (ret);
}
