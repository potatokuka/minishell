/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 12:36:36 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				clear_cmd(t_cmd *cmd, void(*del)(void *))
{
	t_cmd	*delete;

	while (cmd)
	{
		delete = cmd;
		cmd = cmd->next;
		if (delete->builtin)
			del(delete->builtin);
		if (delete->tar_file)
			del(delete->tar_file);
		if (delete->argv)
		{
			fre_array(delete->argv);
			del(delete->argv);
		}
	}
	return (0);
}

int		drop_string(t_data *data, int i)
{
	if (data->argv[i])
		free(data->argv[i]);
	data->argv[i] = NULL;
	return (0);
}

void	print_cur_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	dprintf(2,"-- PRINT CUR CMD STRUCT --\n");
	if (cmd->builtin)
		dprintf(2,"Builtin_%s\n", cmd->builtin);
	if (cmd->io_fd[IN] != -1)
		dprintf(2,"Redir In_%d\n", cmd->io_fd[IN]);
	if (cmd->io_fd[OUT] != -1)
		dprintf(2,"Redir Out_%d\n", cmd->io_fd[OUT]);
	if (cmd->pipe_read_end != -1)
		dprintf(2,"Pipe Read_%d\n", cmd->pipe_read_end);
	if (cmd->tar_file)
		dprintf(2,"Tar File_%s\n", cmd->tar_file);
	if (cmd->argc)
		dprintf(2,"Argc_%d\n", cmd->argc);
	if (cmd->argv)
	{
		while (i < cmd->argc)
		{
			dprintf(2,"ARGV[%d]_%s\n", i, cmd->argv[i]);
			i++;
		}
	}
}

void	print_cmd_full(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmd;
	while (cmd)
	{
		print_cur_cmd(cmd);
		cmd = cmd->next;
	}
}
