/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 13:12:20 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_pid *pid)
{
	int i;

	i = 0;
	while (i < pid->count)
	{
		dprintf(2, "[%d]_%d\n", i, pid->value[i]);
		i++;
	}
	i = 0;
	while (i < pid->count)
	{
		dprintf(2, "waiting pid:%d\n", pid->value[i]);
		waitpid(pid->value[i], &pid->status[i], 0);
		i++;
	}
	ft_free((void **)&pid->value);
	ft_free((void **)&pid->status);
}

/*
 * Add all fds that get opened to a list/array, but no need to remove the current pidfds, maybe rename them though
 * assign the used ones to io_fd[2]
 * close all others i.e. those that dont match to either io_fd[0] io_fd[1]
*/

void	fork_next_and_pipe(t_cmd *cmd, t_var **env, char **envp, t_pid *pid, t_fd_sto *fd, int is_parent)
{
	//Commands that are aids
	//echo hello | cat | cat -n
	//echo hello | cat | echo lol
	//echo aa | sed "s/a/b/g" | sed "s/b/c/g"
	int		status;
	int		pid_temp;
	int		reset_fd[2];

	reset_fd[OUT] = -1;
	reset_fd[IN] = -1;
	pid_temp = fork();
	if (pid_temp != 0)
		ft_add_pid(pid, pid_temp, status);
	if (pid_temp < 0)
		put_error("No Redir Exec Fork Error");
	if (pid_temp == 0)
	{
		ft_reset_pid(pid);
		perror("about to cmd_dispatch this command:");
		perror(cmd->next->argv[0]);
		/*print_cur_cmd(cmd->next);*/

		//Closing my duplicate of senders pipe 
		/*close(cmd->pipfd2[WRITE_FD]);//Does this need protection*/
		//Assigning my read end of pipe
		/*if (cmd->next->pipfd[IN] == -1)*/
			/*cmd->next->pipfd[IN] = cmd->pipfd2[READ_FD];*/
		/*if (cmd->next->pipfd[IN] == -1)*/
		/*{*/
			/*dprintf(2, "Pipe Dup2 in : %d\n", cmd->pipfd2[READ_FD]);*/
			/*if (dup2(cmd->pipfd2[READ_FD], STDIN_FILENO) == -1)*/
				/*put_error("Failed to dup STDIN\n");*/
		/*}*/

		//Checking if the next command wants to pipe
		/*if (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)*/
		/*{*/
			//Closing my duplicate of recievers end of pipe
			/*close(cmd->next->pipfd2[READ_FD]);//Does this need protectoin*/
			//Assigning my write end of pipe
			/*if (cmd->next->pipfd[OUT] == -1)*/
				/*cmd->next->pipfd[OUT] = cmd->next->pipfd2[WRITE_FD];*/
			/*if (cmd->next->pipfd[OUT] == -1)*/
			/*{*/
				/*dprintf(2, "Pipe Dup2 out : %d\n", cmd->next->pipfd2[WRITE_FD]);*/
				/*if(dup2(cmd->next->pipfd2[WRITE_FD], STDOUT_FILENO) == -1)*/
					/*put_error("Failed to dup STDOUT\n");*/
			/*}*/
		/*}*/

		if (cmd->next->io_fd[IN] == -1)
		{
			cmd->next->io_fd[IN] = cmd->pipe_read_end;
			perror("set");
		}
		close_fd(fd, cmd->next->io_fd);
		cmd_dispatch(cmd->next, env, envp, pid);

		//My pipe to my reciever
		/*if (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)*/
			/*close(cmd->next->pipfd2[WRITE_FD]);//Does this need protectoin*/
		//My pipe
		/*close(cmd->pipfd2[READ_FD]);//Does this need protectoin*/

		//FDs have to be closed first, then forked execve can end
		wait_for_children(pid);
		perror("end of child process");
		exit (0);
	}
	else if (is_parent)
	{
		while (cmd->next && cmd->next->pipe_read_end != -1)
		{
			perror("forking child from while loop");
			fork_next_and_pipe(cmd->next, env, envp, pid, fd, 0);
			cmd->next = cmd->next->next;
		}
		if (cmd->next)
			cmd->next = cmd->next->next;

		//Closing my duplicate of receivers pipe
		/*close(cmd->pipfd2[READ_FD]);//Does this need protectoin*/
		//Assinging my write end of the pipe
		/*if (cmd->pipfd[OUT] == -1)*/
			/*cmd->pipfd[OUT] = cmd->pipfd2[WRITE_FD];*/
		/*if (cmd->pipfd[OUT] == -1)*/
		/*{*/
			/*dprintf(2, "Pipe Dup2 out : %d\n", cmd->pipfd2[WRITE_FD]);*/
			/*reset_fd[OUT] = dup(STDOUT_FILENO);*/
			/*if(dup2(cmd->pipfd2[WRITE_FD], STDOUT_FILENO) == -1)*/
				/*put_error("Failed to dup STDOUT\n");*/
		/*}*/
		//for multiple pipes i.e. echo fag | cat | cat, try calling the forking from inside here, rather than inside the child

		close_fd(fd, cmd->io_fd);
		cmd_dispatch(cmd, env, envp, pid);
		/*close(cmd->pipfd2[WRITE_FD]);//Does this need protectoin*/
		/*if (reset_fd[OUT] != -1)*/
			/*if (dup2(reset_fd[OUT], STDOUT_FILENO) == -1)*/
				/*put_error("Failed to dup STDOUT\n");*/
		wait_for_children(pid);
	}
}

void	close_the_shit(t_cmd *cmd)
{
	if (cmd->resetfd[IN] != -1)
	{
		if (dup2(cmd->resetfd[IN], STDIN_FILENO) == -1)
			put_error("Failed to reset STDIN");
		close(cmd->resetfd[IN]);
		cmd->resetfd[IN] = -1;
	}

	if (cmd->resetfd[OUT] != -1)
	{
		if (dup2(cmd->resetfd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to reset STDIN");
		close(cmd->resetfd[OUT]);
		cmd->resetfd[OUT] = -1;
	}

	if (cmd->io_fd[IN] != -1)
		close(cmd->io_fd[IN]);
	if (cmd->io_fd[OUT] != -1)
		close(cmd->io_fd[OUT]);
}

void	dup_redir(t_cmd *cmd)
{
	if (cmd->io_fd[IN] != -1)
	{
		cmd->resetfd[IN] = dup(STDIN);
		dprintf(2, "Dup2 FD in : %d\n", cmd->io_fd[IN]);
		if (cmd->io_fd[IN] != -1 &&
				dup2(cmd->io_fd[IN], STDIN_FILENO) == -1)
			put_error("Failed to dup STDIN");
		if (cmd->io_fd[IN] != -1)
			close(cmd->io_fd[IN]);
	}
	if (cmd->io_fd[OUT] != -1)
	{
		cmd->resetfd[OUT] = dup(STDOUT);
		dprintf(2, "Dup2 FD out : %d\n", cmd->io_fd[OUT]);
		if (cmd->io_fd[OUT] != -1 &&
					dup2(cmd->io_fd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to dup STDOUT");
		if (cmd->io_fd[OUT] != -1)
			close(cmd->io_fd[OUT]);
	}
}

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp, t_pid *pid)
{

	if (cmd->io_fd[IN] != -1 || cmd->io_fd[OUT] != -1)
		dup_redir(cmd);
	if (cmd->builtin)
	{
		// is there a '|', if there is FORK if not, dup2 all the according
		// fds. If there is a '|', fork and then run.
		if (ft_strncmp(cmd->builtin, "exit", 4) == 0)
			ft_exit();
		else if (ft_strncmp(cmd->builtin, "echo", 4) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->builtin, "env", 3) == 0)
			ft_env(envp);
		else if (ft_strncmp(cmd->builtin, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(cmd->builtin, "cd", 2) == 0)
			ft_cd(cmd, *env);
		else if (ft_strncmp(cmd->builtin, "unset", 5) == 0)
			ft_unset(cmd, env);
		else if (ft_strncmp(cmd->builtin, "export", 6) == 0)
			ft_export(cmd, env, envp);
	}
	else
		ft_exec(cmd, *env, envp, pid);
	if (cmd->io_fd[IN] != -1 || cmd->io_fd[OUT] != -1)
		close_the_shit(cmd);
}
