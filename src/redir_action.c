/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 13:36:22 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 12:04:27 by averheij      ########   odam.nl         */
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

void	redir_append(t_fd_sto *fd, t_cmd *cmd)
{
	int file;

	file = open(cmd->tar_file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file < 0)
		put_error("Error with File in Redir Append");
	cmd->io_fd[OUT] = file;
	if (sto_fd(fd, file))
		put_error("Failed to store FD");
}

void	redir_trunc(t_fd_sto *fd, t_cmd *cmd)
{
	int file;

	file = open(cmd->tar_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file < 0)
		put_error("Error with File in Redir trunc");
	cmd->io_fd[OUT] = file;
	if (sto_fd(fd, file))
		put_error("Failed to store FD");
}

void	redir_std_input(t_fd_sto *fd, t_cmd *cmd)
{
	int file;

	file = open(cmd->tar_file, O_RDONLY, 0644);
	if (file < 0)
		put_error("Error with File in Redir input");
	dprintf(2, "Input Redir FD : %d\n", file);
	cmd->io_fd[IN] = file;
	if (sto_fd(fd, file))
		put_error("Failed to store FD");
}

int		open_pipe(t_fd_sto *fd, t_cmd *cmd)
{
	int		pipfd[2];

	if (pipe(pipfd) == -1)
		return (1);
	if (cmd->io_fd[OUT] == -1)
		cmd->io_fd[OUT] = pipfd[OUT];
	cmd->pipe_read_end = pipfd[IN];
	if (sto_fd(fd, pipfd[IN]))
		return (1);
	if (sto_fd(fd, pipfd[OUT]))
		return (1);
	return (0);
}
