/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:42:18 by averheij      #+#    #+#                 */
/*   Updated: 2020/11/06 13:44:27 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **envp, char *prestr)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] != '?')
			ft_printf_fd(1, "%s%s\n", prestr, envp[i]);
		i++;
	}
	return (0);
}

int		ft_export_env(t_var *env)
{
	while (env)
	{
		if (env && env->name && env->name[0] != '?')
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", env->name, env->val);
		env = env->next;
	}
	return (0);
}
