/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 13:36:22 by greed         #+#    #+#                 */
/*   Updated: 2020/06/29 18:29:49 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** check if CMD triggered, if it is not then just run the REDIR normal
** if if not run check the cmd, and then put into the directed file
** **** TAKE FROM HERE >> MOVE TO HERE ****
*/

/*
** check to see what kind of flag is given, direct to correct function 
*/

/*
** once the flag is found, execute the command on the left, into the
** target file on the right
*/

/*
** fork to preserve main process, on child process dup2 stdout to the FD of
** target file, check for builtin cmds, if there execute them as normal,
** if they are not there, send to ft_exec
*/

/*
** pipe everything existing to the left of the cmd and read it into the 
** target to the right
*/

void	redir_append(t_input *inp)
{
	int		pipfd[2];
	int		pid1;
	int		i;
// MAYBE CHECK FIRST FOR BUILTINS THAT REQUIRE MAIN PROCESS, CD
	i = 0;
	while (i < inp->argc)
	{
		if (ft_strncmp(inp->argv[i], ">>", 2) == 0)
		{
			if (!inp->argv[i + 1])
				put_error("syntax error near unexpected token `newline'");
			break ;
		}
		else
			i++;
	}
	if (pipe(pipfd) == -1)
		put_error("Redir append pipfd error");
	pid1 = fork();
	if (pid1 < 0)
		put_error("Redir append fork error");
	if (pid1 == 0)
	{
		/* CHILD PROCESS 1 (LEFT SIDE)
		** ----------------------------- 
		** find '>>' check to make sure there is anything to RIGHT 
		** on the right, check everything on LEFT for builtin CMD
		** if builtin cmd run it, if not run EXEC
		*/
		/* ------------------------------------- */
		int file = open(inp->argv[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (file < 0)
			put_error("Error with File in Redir Append");
			dup2(file, STDOUT_FILENO);	
			close(file);
			if (inp->cmd)
				cmd_dispatch(inp);
			else
				ft_exec(inp);
	}
	close(pipfd[0]);
	close(pipfd[1]);

	waitpid(pid1, NULL, 0);
}

void	redir_append_old(t_input *inp)
{
	int		i;
	int		fd;
	int		ret;
	int		pipfd[2];
	pid_t	cpid;

	pipe(pipfd);
	i = 0;
	cpid = fork();
	printf("inside of REDIR APPEND\n");
	while (inp->argv[i])
	{
		if (ft_strncmp(inp->argv[i], ">>", 2) == 0)
		{
			if (!inp->argv[i + 1])
				put_error("syntax error near unexpected token `newline'");
			printf("FILE TO SAVE TO = %s\n", inp->argv[i+1]);
			fd = open(inp->argv[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0664);
			if (fd < 0)
				put_error("Error with REDIR Append FD");
			ret = dup2(fd, 1);
			if (ret < 0)
				put_error("Error with REDIR Append Dup2");
			return ;
		}
		else
			i++;
	}
}

void	redir_dispatch(t_input *inp)
{
	int		i;

	i = 0;
	printf("INSIDE OF REDIR_DISPATCH\n");
	if (inp->redirs)
	{
		printf("redirs[%d]= %s\n", i, inp->redirs[i]);
		if (ft_strncmp(inp->redirs[i], ">>", 2) == 0)
			redir_append(inp);
		/* else if (ft_strncmp(inp->redirs[i], "<", 1)) */
		/* 	redir_std_input(inp); */
		/* else if (ft_strncmp(inp->redirs[i], ">", 1)) */
		/* 	redir_std_out(inp); */
	}
	perror("didnt go inside");
	return ;
}
