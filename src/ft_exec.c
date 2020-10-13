/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:47:28 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/12 15:39:18 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/*
** Return 1 if a char array string matches the str ptr string
*/

int		file_match(char file[], char *file2)
{
	int		i;

	i = 0;
	while ((file[i] || file2[i]) && i < 256)
	{
		if (file[i] != file2[i])
			return (0);
		i++;
	}
	if (i == 256 && file2[i])
		return (0);
	return (1);
}

/*
** Search the $PATH variable directories a file matching with name
** matching string exec
*/

int		search_dir(DIR *dirp, char *exec)
{
	struct dirent	*file;

	file = (void *)1;
	while (file)
	{
		file = readdir(dirp);
		if (file)
		{
			if (file_match(file->d_name, exec))
			{
				return (1);
			}
		}
	}
	return (0);
}

int		get_env_path_exec(char **pathname, char *exec, t_var *env)
{
	char			**paths;
	DIR				*dirp;
	int				i;

	*pathname = get_env_val("PATH", env, 4);
	dprintf(2,"exec:%s\n", exec);
	paths = ft_split(*pathname, ':');
	if (!paths)
		put_error(strerror(errno));
	*pathname = (void *)0;
	i = 0;
	while (pathname && !*pathname && paths[i])
	{
		dirp = opendir(paths[i]);
		if (dirp)
		{
			if (search_dir(dirp, exec))
			{
				*pathname = ft_3strjoin(paths[i], "/", exec);
				if (!*pathname)
				{
					closedir(dirp);
					return (1);
				}
			}
			closedir(dirp);
		}
		i++;
	}
	free_array_null(paths);
	return (0);
}

/*
** Attempt to find and execute an executable based on a given absolute or 
** relative path, or $PATH identifier.
*/

int		griffin_try(t_cmd *cmd, char *pathname, char **envp, t_pid *pid)
{
	t_pid	*new;
	int		pid_temp;

	pid_temp = fork();
	if (pid_temp != 0)
		if (ft_add_pid(pid, pid_temp))
			return (1);
	if (pid_temp < 0)
		return (1);
	if (pid_temp == 0)
	{
		execve(pathname, cmd->argv, envp);
		g_signal_exit = -2;
		return (1);
	}
	free(pathname);
	return (0);
}

int		ft_exec(t_cmd *cmd, t_var *env, char **envp, t_pid *pid)
{
	char	*path;
	char	*pathname;
	int		status;

	dprintf(2,"EXEC -------------\n");
	if (cmd->argc && cmd->argv[0][0] == '.')
	{
		if (get_path(&path))
			return (2);
		pathname = ft_strjoin(path, cmd->argv[0] + 1);
		free(path);
		if (!pathname)
			return (2);
	}
	else if (cmd->argc && cmd->argv[0][0] == '/')
	{
		pathname = cmd->argv[0];
		cmd->argv[0] = ft_strrchr(cmd->argv[0], '/');
	}
	else
	{
		if (get_env_path_exec(&pathname, cmd->argv[0], env))
			return (2);
		if (!pathname)
		{
			dprintf(2,"%s: command not found\n", cmd->argv[0]);
			return (1);
		}
	}
	dprintf(2,"pathname:%s\n", pathname);
	if (griffin_try(cmd, pathname, envp, pid))
		return (2);
	return (0);
}
