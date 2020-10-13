/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 13:53:40 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 13:53:41 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_var(t_var *env)
{
	if (!env)
		return ;
	if (env->name)
		ft_free((void **)&env->name);
	if (env->val)
		ft_free((void **)&env->val);
	if (env->next && env->next != NULL)
		free_var(env->next);
	free(env);
}

int			dup_redir(t_cmd *cmd, int is_child)
{
	if (cmd->io_fd[IN] != -1)
	{
		if (!is_child)
			cmd->resetfd[IN] = dup(STDIN);
		dprintf(2, "Dup2 FD in : %d\n", cmd->io_fd[IN]);
		if (cmd->io_fd[IN] != -1)
			if (dup2(cmd->io_fd[IN], STDIN_FILENO) == -1)
				return (1);
		if (cmd->io_fd[IN] != -1)
			close(cmd->io_fd[IN]);
	}
	if (cmd->io_fd[OUT] != -1)
	{
		if (!is_child)
			cmd->resetfd[OUT] = dup(STDOUT);
		dprintf(2, "Dup2 FD out : %d\n", cmd->io_fd[OUT]);
		if (cmd->io_fd[OUT] != -1)
			if (dup2(cmd->io_fd[OUT], STDOUT_FILENO) == -1)
				return (1);
		if (cmd->io_fd[OUT] != -1)
			close(cmd->io_fd[OUT]);
	}
	return (0);
}
