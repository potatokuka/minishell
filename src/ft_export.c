/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:09:44 by greed         #+#    #+#                 */
/*   Updated: 2020/11/06 13:42:26 by averheij      ########   odam.nl         */
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
			ft_printf_fd(2, "export: %s: not a valid value\n", str);
			return (1);
		}
		a++;
	}
	return (0);
}

int		export_append(char *str, t_var **env, ssize_t eq)
{
	char	*val;

	str[eq - 1] = '\0';
	if (validate_env_name(str))
		return (1);
	val = get_env_val(str, *env, ft_strlen(str));
	if (!val)
		val = "";
	val = ft_strjoin(val, &str[eq + 1]);
	if (!val)
		return (2);
	if (env_set_val(str, env, val))
	{
		free(val);
		return (2);
	}
	free(val);
	return (0);
}

int		export_single(char *str, t_var **env)
{
	ssize_t	eq;

	eq = ft_strclen(str, '=');
	if (eq < (ssize_t)ft_strlen_lib(str) && !iscset(str[0], "=+\0"))
	{
		if (eq - 1 >= 0 && str[eq - 1] == '+')
			return (export_append(str, env, eq));
		else
		{
			str[eq] = '\0';
			if (validate_env_name(str))
				return (1);
			if (env_set_val(str, env, &str[eq + 1]))
				return (2);
		}
	}
	else if (validate_env_name(str))
		return (1);
	return (0);
}

int		ft_export(t_cmd *cmd, t_var **env)
{
	size_t	i;
	int		ret;
	int		temp;

	if (cmd->argc == 0)
		return (ft_export_env(*env));
	ret = 0;
	i = 0;
	while (cmd->argv[i])
	{
		temp = export_single(cmd->argv[i], env);
		if (temp != 0)
			ret = temp;
		i++;
	}
	cmd->update_env = 1;
	return (ret);
}
