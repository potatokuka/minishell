/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:09:44 by greed         #+#    #+#                 */
/*   Updated: 2020/10/06 14:37:12 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(t_cmd *cmd, t_var **env, char **envp)
{
	size_t	i;
	size_t	tmp;
	int		a;

	dprintf(2,"argc = %d\n", cmd->argc);
	if (cmd->argc == 0)
	{
		ft_env(envp);
		return (0);
	}
	i = 0;
	while (cmd->argv[i])
	{
		dprintf(2,"\t-- Export --\nargv[%zu]_%s\n", i, cmd->argv[i]);
		tmp = ft_strclen(cmd->argv[i], '=');
		dprintf(2,"\n\ntmp =_%zu\n", tmp);
		if (tmp < ft_strlen_lib(cmd->argv[i]))
		{
			a = 0;
			while (a < tmp)
			{
				dprintf(2, "testing char %c_%d_%d_%d\n", cmd->argv[i][a], a, a, ft_env_char(cmd->argv[i][a], !a));
				if (!ft_env_char(cmd->argv[i][a], !a))
				{
					ft_printf_fd(2, "Export: %s: not a valid identifier\n", cmd->argv[i]);
					return (1);
				}
				a++;
			}
			cmd->argv[i][tmp] = '\0';
			dprintf(2,"testing argv[%zu]_%s\n%s\n", i, cmd->argv[i], &cmd->argv[i][tmp + 1]);
			env_set_val(cmd->argv[i], env,
					&cmd->argv[i][tmp + 1]);
		}
		i++;
	}
	cmd->update_env = 1;
	return (0);
}
