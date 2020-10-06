/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 12:42:16 by greed         #+#    #+#                 */
/*   Updated: 2020/10/05 17:48:35 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_home(t_var *env)
{
	char	*home;

	home = get_env_val("HOME", env, 4);
	dprintf(2,"CD HOME CHECK %s\n", home);
	if (!home)
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_printf_fd(2, "cd: %s: %s\n", strerror(errno), home);
		return (1);
	}
	return (0);
}

int		ft_cd(t_cmd *cmd, t_var *env)
{
	if (cmd->argc == 0 || (ft_strcmp(cmd->argv[0], "~") == 0))
		return (cd_home(env));
	if (chdir(cmd->argv[0]) == -1)
		return (error_builtin(cmd, 1));
	return (0);
}
