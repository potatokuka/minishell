/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/09/23 11:24:51 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_the_shit(t_cmd *cmd)
{
	if (cmd->pipe)
	{
		if (cmd->pipfd[0] != -1)
			close(cmd->pipfd[0]);
		if (cmd->pipfd[1] != -1)
			close(cmd->pipfd[1]);
		if (cmd->pid1 == 0)
			exit (1);
	}
}

void	dup_redir(t_cmd *cmd)
{
	if (cmd->pipe && ft_is_redir(cmd->pipe))
	{
		dprintf(2, "Dup2 FD in : %d\n", cmd->pipfd[0]);
		if (cmd->pipfd[1] != -1 &&
					dup2(cmd->pipfd[1], STDOUT_FILENO) == -1)
			put_error("Failed to dup STDOUT for Child");
		if (cmd->pipfd[0] != -1 &&
				dup2(cmd->pipfd[0], STDIN_FILENO) == -1)
			put_error("Failed to dup STDIN for Child");
		if (cmd->pipfd[0] != -1)
			close(cmd->pipfd[0]);
		if (cmd->pipfd[1] != -1)
			close(cmd->pipfd[1]);
	}
}

void	set_fork_redir(t_cmd *cmd)
{
		// if (ft_is_valid_pipe(cmd))
		// {
		// 	// cmd->pid1 = fork();
		// 	// if (cmd->pid1 < 0)
		// 	// 	put_error("Redir Fork Error");
		// 	// if (cmd->pid1 == 0)
		// 	// {	
		// 	// 	if (dup2(STDOUT, STDIN) == -1)
		// 	// 		put_error("Failed to dup STDOUT to STDIN for Pipe");
		// 	// 	if (cmd->pipfd[0] != -1)
		// 	// 		close(cmd->pipfd[0]);
		// 	// 	if (cmd->pipfd[1] != -1)
		// 	// 		close(cmd->pipfd[1]);
		// 	// }
		// 	// else
		// 	// {
		// 	// 	waitpid(cmd->pid1, NULL, 0);
		// 	// }
		// 	if (pipe(cmd->pipfd) == -1)
		// 	{
		// 		free(cmd);
		// 		put_error("Failed in Pipe");
		// 	}
		// 	cmd->pipfd[0] = cmd->pipfd[0];
		// 	if (cmd->next && cmd->next->pipe[0] == '|')
		// 		cmd->next->pipfd[1] = cmd->next->pipfd[1];
		// }
		if (cmd->pipe && ft_is_redir(cmd->pipe))
		{
			cmd->pid1 = fork();
			if (cmd->pid1 < 0)
				put_error("Redir Fork Error");
			if (cmd->pid1 == 0)
			{
				dprintf(2, "Dup2 FD in : %d\n", cmd->pipfd[0]);
				if (cmd->pipfd[1] != -1 &&
						dup2(cmd->pipfd[1], STDOUT_FILENO) == -1)
					put_error("Failed to dup STDOUT for Child");
				if (cmd->pipfd[0] != -1 &&
						dup2(cmd->pipfd[0], STDIN_FILENO) == -1)
					put_error("Failed to dup STDIN for Child");
				if (cmd->pipfd[0] != -1)
					close(cmd->pipfd[0]);
				if (cmd->pipfd[1] != -1)
					close(cmd->pipfd[1]);
			}
			else
			{
				close(cmd->pipfd[0]);
				close(cmd->pipfd[1]);
				waitpid(cmd->pid1, NULL, 0);
			}
		}
}

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp)
{
	
	if (cmd->pipe && ft_is_redir(cmd->pipe))
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
		ft_exec(cmd, *env, envp);
	if (cmd->pipe && cmd->pid1 == 0)
		close_the_shit(cmd);
}
