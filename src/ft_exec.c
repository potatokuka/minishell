/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:47:28 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/29 15:51:53 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_env_path_exec(char **pathname, char *exec, t_var *env)
{
	char			**paths;
	int				i;
	struct stat		unused;

	*pathname = get_env_val("PATH", env, 4);
	paths = ft_split(*pathname, ':');
	if (!paths)
		put_error(strerror(errno));
	*pathname = (void *)0;
	i = 0;
	while (!*pathname && paths[i])
	{
		*pathname = ft_3strjoin(paths[i], "/", exec);
		if (!*pathname || stat(*pathname, &unused) != -1)
		{
			free_array_null(paths);
			return ((*pathname) ? 0 : 1);
		}
		free(*pathname);
		*pathname = (void *)0;
		i++;
	}
	free_array_null(paths);
	return (0);
}

/*
** Attempt to find and execute an executable based on a given absolute or
** relative path, or $PATH identifier.
*/

int			griffin_try(t_cmd *cmd, char *pathname, char **envp, t_pid *pid)
{
	int		pid_temp;

	pid_temp = fork();
	if (pid_temp != 0)
		if (ft_add_pid(pid, pid_temp))
			return (2);
	if (pid_temp < 0)
		return (1);
	if (pid_temp == 0)
	{
		execve(pathname, cmd->argv, envp);
		g_signal_exit = -2;
		ft_printf_fd(2, "%s: permission denied\n", cmd->argv[0]);
		exit(126);
		/*return (2);*/
	}
	free(pathname);
	return (0);
}

static int	get_relative_pathname(t_cmd *cmd, char **pathname)
{
	char	*path;

	if (get_path(&path))
		return (2);
	*pathname = ft_strjoin(path, cmd->argv[0] + 1);
	free(path);
	if (!pathname)
		return (2);
	return (0);
}

int			ft_exec(t_cmd *cmd, t_var *env, char **envp, t_pid *pid)
{
	char	*pathname;

	if (cmd->argc && cmd->argv[0][0] == '.')
	{
		if (get_relative_pathname(cmd, &pathname))
			return (2);
	}
	else if (cmd->argc && cmd->argv[0][0] == '/')
		pathname = ft_strdup(cmd->argv[0]);
	else
	{
		if (get_env_path_exec(&pathname, cmd->argv[0], env))
			return (2);
		if (!pathname)
		{
			ft_printf_fd(2, "%s: command not found\n", cmd->argv[0]);
			return (127);
		}
	}
	return (griffin_try(cmd, pathname, envp, pid));
}
