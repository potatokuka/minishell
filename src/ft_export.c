/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:09:44 by greed         #+#    #+#                 */
/*   Updated: 2020/10/08 11:54:42 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export2(t_cmd *cmd, t_var **env, size_t tmp, size_t a)
{
	size_t i;

	i = 0;
	while (cmd->argv[i])
	{
		tmp = ft_strclen(cmd->argv[i], '=');
		if (tmp < ft_strlen_lib(cmd->argv[i]))
		{
			a = 0;
			while (a < tmp)
			{
				if (!ft_env_char(cmd->argv[i][a], !a))
				{
					ft_printf_fd(2, "%s: not a valid value\n", cmd->argv[i]);
					return (1);
				}
				a++;
			}
			cmd->argv[i][tmp] = '\0';
			if (env_set_val(cmd->argv[i], env, &cmd->argv[i][tmp + 1]))
				return (2);
		}
		i++;
	}
	return (0);
}

int		ft_export(t_cmd *cmd, t_var **env, char **envp)
{
	size_t	tmp;
	int		a;
	int		res;

	if (cmd->argc == 0)
	{
		ft_env(envp);
		return (0);
	}
	res = export2(cmd, env, tmp, a);
	if (res)
		return (res);
	cmd->update_env = 1;
	return (0);
}
