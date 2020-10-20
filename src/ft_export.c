/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:09:44 by greed         #+#    #+#                 */
/*   Updated: 2020/10/20 14:53:21 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		validate_env_name(char *str)
{
	size_t		a;

	a = 0;
	while (str[a])
	{
		if (!ft_env_char(str[a], !a))
		{
			ft_printf_fd(2, "%s: not a valid value\n", str);
			return (1);
		}
		a++;
	}
	return (0);
}

int		ft_export(t_cmd *cmd, t_var **env, char **envp)
{
	size_t	tmp;
	size_t 	i;

	if (cmd->argc == 0)
	{
		ft_env(envp);
		return (0);
	}
	i = 0;
	while (cmd->argv[i])
	{
		tmp = ft_strclen(cmd->argv[i], '=');
		if (tmp < ft_strlen_lib(cmd->argv[i]))
		{
			char	*val;

			if (tmp - 1 >= 0 && cmd->argv[i][tmp - 1] == '+')
			{
				cmd->argv[i][tmp - 1] = '\0';
				if (validate_env_name(cmd->argv[i]))
					return (1);
				val = get_env_val(cmd->argv[i], *env, ft_strlen(cmd->argv[i]));
				if (!val)
					val = "";
				dprintf(2, "%s\t%s\n", val, &cmd->argv[i][tmp + 1]);
				val = ft_strjoin(val, &cmd->argv[i][tmp + 1]);
				dprintf(2, "%s\n", val);
				if (!val)
					return (2);
				if (env_set_val(cmd->argv[i], env, val))
				{
					free(val);
					return (2);
				}
				free(val);
			}
			else
			{
				cmd->argv[i][tmp] = '\0';
				if (validate_env_name(cmd->argv[i]))
					return (1);
				if (env_set_val(cmd->argv[i], env, &cmd->argv[i][tmp + 1]))
					return (2);
			}
		}
		i++;
	}
	cmd->update_env = 1;
	return (0);
}
