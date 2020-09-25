/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/09/25 13:53:37 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				clear_cmd(t_cmd *cmd, void(*del)(void *))
{
	t_cmd	*delete;

	while (cmd)
	{
		delete = cmd;
		perror("moving cmd->NEXT in CLEAR_CMD");
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
	if (cmd->pipfd[IN] != -1)
		dprintf(2,"Redir In_%d\n", cmd->pipfd[IN]);
	if (cmd->pipfd[OUT] != -1)
		dprintf(2,"Redir Out_%d\n", cmd->pipfd[OUT]);
	if (cmd->pipfd2[WRITE_FD] != -1)
		dprintf(2,"Pipe Write_%d\n", cmd->pipfd2[WRITE_FD]);
	if (cmd->pipfd2[READ_FD] != -1)
		dprintf(2,"Pipe Read_%d\n", cmd->pipfd2[READ_FD]);
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
