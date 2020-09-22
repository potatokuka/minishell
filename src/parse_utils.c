/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 18:11:21 by greed         ########   odam.nl         */
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
		if (delete->pipe)
			del(delete->pipe);
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
	if (cmd->pipe)
		dprintf(2,"Pipe_%s\n", cmd->pipe);
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
		dprintf(2,"-- PRINT CUR CMD STRUCT --\n");
		if (cmd->builtin)
			dprintf(2,"Builtin_%s\n", cmd->builtin);
		if (cmd->pipe)
			dprintf(2,"Pipe_%s\n", cmd->pipe);
		if (cmd->tar_file)
			dprintf(2,"Tar File_%s\n", cmd->tar_file);
		if (cmd->argc)
			dprintf(2,"Argc_%d\n", cmd->argc);
		if (cmd->argv)
		{
			i = 0;
			while (i < cmd->argc)
			{
				dprintf(2,"ARGV_%s\n",cmd->argv[i]);
				i++;
			}
		}
		perror("Moving cmd->NEXT in Print CMD FULL");
		cmd = cmd->next;
	}
}
