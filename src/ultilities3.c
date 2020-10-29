/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 13:53:40 by greed         #+#    #+#                 */
/*   Updated: 2020/10/28 15:05:07 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Return 1 if a char array string matches the str ptr string
*/

int			file_match(char file[], char *file2)
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

void		put_error_data_cmd(t_data *data, t_cmd *cmd, char *error)
{
	free(cmd);
	put_error_data(data, error);
}

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
		if (cmd->io_fd[OUT] != -1)
			if (dup2(cmd->io_fd[OUT], STDOUT_FILENO) == -1)
				return (1);
		if (cmd->io_fd[OUT] != -1)
			close(cmd->io_fd[OUT]);
	}
	return (0);
}

char		*safe_strljoin(char *s1, ssize_t l1, char *s2, t_data *dt)
{
	char	*res;

	s1 = handle_escapes_envs(dt, ft_strldup(s1, l1), '"');
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
