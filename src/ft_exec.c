/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:47:28 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/23 20:04:04 by greed         ########   odam.nl         */
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
	/*dprintf(2, "file: %s file2: %s\n", file, file2);*/
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
		if (file)//Also returns NULL on error, so do we need checks in here?
		{
			if (file_match(file->d_name, exec))//Might need to check file type DT_REG || DT_LNK
			{
				/*printf("\tf:%s %d %d %d\n", file->d_name, file->d_type, DT_REG, file_match(file->d_name, exec));*/
				return (1);
			}
			/*free(file);*/
		}
	}
	return (0);
}

char	*get_env_path_exec(char *exec, t_var *env)
{
	char			**paths;
	char			*temp;
	DIR				*dirp;

	temp = get_env_val("PATH", env, 4);
	dprintf(2,"exec:%s\n", exec);
	/*printf("$PATH:%s\n", temp);*/
	paths = ft_split(temp, ':');
	if (!paths)
		put_error(strerror(errno));
	temp = (void *)0;
	while (!temp && *paths)
	{
		/*printf("path:%s\n", *paths);*/
		dirp = opendir(*paths);
		if (dirp)//NULL on error, but do we care? maybe theres shit values in PATH, do we really want to throw then?
		{
			if (search_dir(dirp, exec))
				temp = ft_3strjoin(*paths, "/", exec);
			/*free(dirp);*/
		}
		paths++;
	}
	return (temp);
}

/*
** Attempt to find and execute an executable based on a given absolute or 
** relative path, or $PATH identifier.
*/

void	griffin_try(t_cmd *cmd, char *pathname, char **envp, t_data *data)
{
	int		status;
	t_pid	*new;

	data->pid->value[data->pid->count] = fork();
	ft_add_pid(data->pid, data->pid->value[data->pid->count], status, data);
	if (data->pid->value[data->pid->count] < 0)
		put_error("No Redir Exec Fork Error");
	if (data->pid->value[data->pid->count] == 0)
	{
		execve(pathname, cmd->argv, envp);
		put_error("execve 2");
	}
	else
	{
		//Add all pids to an array (or vector if youre a fag) and close them later, or a linked list if you love leaks
		waitpid(cmd->pid1, &status, 0);
	}
}

void	ft_exec(t_cmd *cmd, t_var *env, char **envp, t_data *data)
{
	//TODO Check how bash responds to errno and -1 response
	//TODO Check if there is a MAX_ARGS
	char	*path;
	char	*pathname;
	pid_t	pid;
	int		status;

	dprintf(2,"EXEC -------------\n");
	if (cmd->argc && cmd->argv[0][0] == '.')
	{
		path = get_path();
		pathname = ft_strjoin(path, cmd->argv[0] + 1);
		free(path);
	}
	else if (cmd->argc && cmd->argv[0][0] == '/')
	{
		pathname = cmd->argv[0];
		cmd->argv[0] = ft_strrchr(cmd->argv[0], '/');
	}
	else
	{
		pathname = get_env_path_exec(cmd->argv[0], env);
		if (!pathname)
		{
			dprintf(2,"%s: command not found\n", cmd->argv[0]);
			return ;
		}
	}
	dprintf(2,"pathname:%s\n", pathname);
	griffin_try(cmd, pathname, envp, data);
}
