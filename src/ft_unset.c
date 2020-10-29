/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 13:43:46 by greed         #+#    #+#                 */
/*   Updated: 2020/10/29 15:10:08 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** send each argv to get removed from ENV if they exist
*/

int		is_valid_env_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_env_char(str[i], (i == 0) ? 1 : 0))
		i++;
	return (!str[i]);
}

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
		if (!is_valid_env_name(cmd->argv[i]))
		{
			ret = 1;
			ft_printf_fd(2, "Error: unset: '%s' is invalid\n", cmd->argv[i]);
		}
		else
			unset_env(env, cmd->argv[i]);
		i++;
	}
	cmd->update_env = 1;
	return (ret);
}
