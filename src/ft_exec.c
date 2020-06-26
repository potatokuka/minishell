/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:47:28 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/25 14:45:52 by averheij      ########   odam.nl         */
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
		if (file)//Also returns NULL on error, so do we need checks in here?
		{
			if (file_match(file->d_name, exec))//Might need to check file type DT_REG || DT_LNK
			{
				printf("\tf:%s %d %d %d\n", file->d_name, file->d_type, DT_REG, file_match(file->d_name, exec));
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
	printf("exec:%s\n", exec);
	printf("$PATH:%s\n", temp);
	paths = ft_split(temp, ':');
	if (!paths)
		put_error(strerror(errno));
	temp = (void *)0;
	while (!temp && *paths)
	{
		printf("path:%s\n", *paths);
		dirp = opendir(*paths);
		if (dirp)//NULL on error, but do we care? maybe theres shit values in PATH, do we really want to throw then?
		{
			if (search_dir(dirp, exec))
				temp = ft_combine_str(*paths, "/", exec);
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

void	ft_exec(t_input *inp)
{
	//TODO Check how bash responds to errno and -1 response
	//TODO Check if there is a MAX_ARGS
	char	*path;
	char	*pathname;
	pid_t	pid;
	int		status;

	printf("EXEC -------------\n");
	if (inp->argc && inp->argv[0][0] == '.')
	{
		path = get_path();
		pathname = ft_strjoin(path, inp->argv[0] + 1);
		free(path);
	}
	else if (inp->argc && inp->argv[0][0] == '/')
	{
		pathname = inp->argv[0];
		inp->argv[0] = ft_strrchr(inp->argv[0], '/');
	}
	else
	{
		pathname = get_env_path_exec(inp->cmd, inp->env);
		if (!pathname)
		{
			printf("%s: command not found\n", inp->cmd);
			return ;
		}
	}
	printf("pathname:%s\n", pathname);
	pid = fork();
	if (pid == -1)
		put_error(strerror(errno));
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		execve(pathname, inp->argv, inp->envp);
		put_error(strerror(errno));
	}
}