/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 13:50:33 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp)
{
	if (cmd->builtin)
	{
		if (cmd->pipe && ((ft_strcmp(cmd->pipe, ">>") == 0 ||
					ft_strcmp(cmd->pipe, ">") == 0) ||
				ft_strcmp(cmd->pipe, "<") == 0))
		{
			if (cmd->pipfd[1] != -1 &&
					dup2(cmd->pipfd[0], STDOUT_FILENO) == -1)
				put_error("Failed to dup STDOUT for Child");
			if (cmd->pipfd[1] != -1 &&
                    dup2(cmd->pipfd[1], STDOUT) == -1)
				put_error("Failed to dup STDIN for Child");
		}
		if (ft_strncmp(cmd->builtin, "exit", 4) == 0)
			ft_exit(cmd);
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
			ft_export(cmd, env);
	}
	else
		ft_exec(cmd, *env, envp);
}
