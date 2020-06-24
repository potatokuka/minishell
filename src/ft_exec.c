/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 16:47:28 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/24 17:34:50 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_input *inp)
{
	//TODO allow for finding execs from path
	//TODO Check how bash responds to errno and -1 response
	//TODO Check if there is a MAX_ARGS
	char	*path;
	char	*pathname;
	pid_t	pid;
	int		status;

	printf("EXEC -------------\n");
	if (inp->argv[0][0] == '.')
	{
		path = get_path();
		printf("path:%s\n", path);
		pathname = ft_strjoin(path, inp->argv[0] + 1);
		free(path);
	}
	else if (inp->argv[0][0] == '/')
	{
		pathname = inp->argv[0];
		inp->argv[0] = ft_strrchr(inp->argv[0], '/');
	}
	printf("pathname:%s\n", pathname);

	pid = fork();
	if (pid == -1)
		printf("Error in Exec");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		execve(pathname, inp->argv, inp->envp);
		put_error(strerror(errno));
	}
}
