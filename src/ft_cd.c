/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 12:42:16 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 14:31:42 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(t_input *inp)
{
	char	*home;

	home = get_env_val("HOME", inp->env, 4);
	printf("CD HOME CHECK %s\n", home);
	if (!home)
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return ;
	}
	if (chdir(home) == -1)
	{
		ft_printf_fd(2, "cd: %s: %s\n", strerror(errno), home);
		return ;
	}
}

void	ft_cd(t_input *inp)
{
	char	*path;

	if (inp->argc == 0)
		return (cd_home(inp));
	path = ft_strdup(inp->argv[0]);
	if (!path)
		put_error("Error inside of CD");
	if (chdir(path) == -1)
	{
		free(path);
		return (error_builtin(inp));
	}
	printf("inside cd\n%s\n", inp->argv[0]);
}
