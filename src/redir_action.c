/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 13:36:22 by greed         #+#    #+#                 */
/*   Updated: 2020/07/08 18:36:58 by averheij      ########   odam.nl         */
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
	int		i;
// MAYBE CHECK FIRST FOR BUILTINS THAT REQUIRE MAIN PROCESS, CD
	i = 0;
	/* if (pipe(inp->cmd->pipfd) == -1) */
	/* 	put_error("Redir append pipfd error"); */
	inp->cmd->pid1 = fork();
	if (inp->cmd->pid1 < 0)
		put_error("Redir append fork error");
	if (inp->cmd->pid1 == 0)
	{
		/* CHILD PROCESS 1 (LEFT SIDE)
		** ----------------------------- 
		** find '>>' check to make sure there is anything to RIGHT 
		** on the right, check everything on LEFT for builtin CMD
		** if builtin cmd run it, if not run EXEC
		*/
		/* ------------------------------------- */
		perror("seg check");
		printf("tar check_%s\n", inp->cmd->tar_file);
		int file = open(inp->cmd->tar_file, O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (file < 0)
			put_error("Error with File in Redir Append");
		dup2(file, STDOUT_FILENO);
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */
		close(file);
	}
	else
	{
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */

		/* this is not stopping after print */
		waitpid(inp->cmd->pid1, NULL, 0);
	}
}

void		redir_trunc(t_input *inp)
{
	int		i;
// MAYBE CHECK FIRST FOR BUILTINS THAT REQUIRE MAIN PROCESS, CD
	i = 0;
	/* if (pipe(inp->cmd->pipfd) == -1) */
	/* 	put_error("Redir append pipfd error"); */
	inp->cmd->pid1 = fork();
	if (inp->cmd->pid1 < 0)
		put_error("Redir append fork error");
	if (inp->cmd->pid1 == 0)
	{
		/* CHILD PROCESS 1 (LEFT SIDE)
		** ----------------------------- 
		** find '>>' check to make sure there is anything to RIGHT 
		** on the right, check everything on LEFT for builtin CMD
		** if builtin cmd run it, if not run EXEC
		*/
		/* ------------------------------------- */
		perror("seg check");
		printf("tar check_%s\n", inp->cmd->tar_file);
		int file = open(inp->cmd->tar_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (file < 0)
			put_error("Error with File in Redir Append");
		dup2(file, STDOUT_FILENO);
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */
		close(file);
	}
	else
	{
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */

		/* this is not stopping after print */
		waitpid(inp->cmd->pid1, NULL, 0);
	}
}

void		redir_std_input(t_input *inp)
{
	int		i;
// MAYBE CHECK FIRST FOR BUILTINS THAT REQUIRE MAIN PROCESS, CD
	i = 0;
	/* if (pipe(inp->cmd->pipfd) == -1) */
	/* 	put_error("Redir input pipfd error"); */
	inp->cmd->pid1 = fork();
	if (inp->cmd->pid1 < 0)
		put_error("Redir input fork error");
	if (inp->cmd->pid1 == 0)
	{
		/* CHILD PROCESS 1 (LEFT SIDE)
		** ----------------------------- 
		** find '>>' check to make sure there is anything to RIGHT 
		** on the right, check everything on LEFT for builtin CMD
		** if builtin cmd run it, if not run EXEC
		*/
		/* ------------------------------------- */
		perror("seg check");
		printf("tar check_%s\n", inp->cmd->tar_file);
		int file = open(inp->cmd->tar_file, O_RDONLY, 0664);
		if (file < 0)
			put_error("Error with File in Redir input");
		/* dup2(file, inp->cmd->pipfd[1]); */
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */
		/* close(file); */
		/*if (inp->cmd->builtin)*/
		/*{*/
			/*cmd_dispatch(inp);*/
			/*exit(1);*/
		/*}*/
		/* else */
		/* 	ft_exec(inp); */
	}
	else
	{
		/* close(inp->cmd->pipfd[0]); */
		/* close(inp->cmd->pipfd[1]); */

		/* this is not stopping after print */
		waitpid(inp->cmd->pid1, NULL, 0);
	}
}
