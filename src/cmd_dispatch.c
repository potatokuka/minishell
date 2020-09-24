/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/09/24 12:16:35 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_next_and_pipe(t_cmd *cmd, t_var **env, char **envp, t_data *data)
{
	int		status;

	cmd->pid1 = fork();
	if (cmd->pid1 < 0)
		put_error("No Redir Exec Fork Error");
	if (cmd->pid1 == 0)
	{	
		close(cmd->pipfd2[WRITE_FD]);
		if (cmd->next->pipfd[IN] == -1)
			cmd->next->pipfd[IN] = cmd->pipfd2[READ_FD];
		else
			close(cmd->pipfd2[READ_FD]);
		//This is intended to fork the next child if needed, and pipe to them, but doesn't work
		// if (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)
		// 	fork_next_and_pipe(cmd->next->next, env, envp);
		cmd_dispatch(cmd->next, env, envp, data);
		close(cmd->pipfd2[READ_FD]);
		dprintf(2, "end of child process\n");
		exit (0);
	}
	else
	{
		close(cmd->pipfd2[READ_FD]);
		if (cmd->pipfd[OUT] == -1)
			cmd->pipfd[OUT] = cmd->pipfd2[WRITE_FD];
		else
			close(cmd->pipfd2[READ_FD]);
		//Add all pids to an array (or vector if youre a fag) and close them later, or a linked list if you love leaks
		cmd_dispatch(cmd, env, envp, data);
		close(cmd->pipfd2[WRITE_FD]);
		waitpid(cmd->pid1, &status, 0);
		//This is intended to skip over every cmd that is going to be forked and piped by the child
		// while (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)
		cmd->next = cmd->next->next;
	}
}

void	close_the_shit(t_cmd *cmd)
{
	if (cmd->pid1 == 0)
		exit (1);
	if (cmd->resetfd[IN] != -1 && dup2(cmd->resetfd[IN], STDIN_FILENO) == -1)
		put_error("Failed to reset STDIN");
	if (cmd->resetfd[OUT] != -1 && dup2(cmd->resetfd[OUT], STDOUT_FILENO) == -1)
		put_error("Failed to reset STDIN");
	cmd->resetfd[IN] = -1;
	cmd->resetfd[OUT] = -1;
}

void	dup_redir(t_cmd *cmd)
{
	if (cmd->pipfd[IN] != -1)
	{
		cmd->resetfd[IN] = dup(STDIN);
		dprintf(2, "Dup2 FD in : %d\n", cmd->pipfd[IN]);
		if (cmd->pipfd[IN] != -1 &&
				dup2(cmd->pipfd[IN], STDIN_FILENO) == -1)
			put_error("Failed to dup STDIN for Child");
		if (cmd->pipfd[IN] != -1)
			close(cmd->pipfd[IN]);
	}
	if (cmd->pipfd[OUT] != -1)
	{
		cmd->resetfd[OUT] = dup(STDOUT);
		dprintf(2, "Dup2 FD out : %d\n", cmd->pipfd[OUT]);
		if (cmd->pipfd[OUT] != -1 &&
					dup2(cmd->pipfd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to dup STDOUT for Child");
		if (cmd->pipfd[OUT] != -1)
			close(cmd->pipfd[OUT]);
	}
}

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp, t_data *data)
{

	if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
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
		if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
			close_the_shit(cmd);
	}
	else
		ft_exec(cmd, *env, envp, data);
	if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
		close_the_shit(cmd);
}
