/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/07/03 20:50:21 by greed         ########   odam.nl         */
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
	printf("-- PRINT CUR CMD STRUCT --\n");
	if (cmd->builtin)
		printf("Builtin_%s\n", cmd->builtin);
	if (cmd->pipe)
		printf("Pipe_%s\n", cmd->pipe);
	if (cmd->tar_file)
		printf("Tar File_%s\n", cmd->tar_file);
	if (cmd->argc)
		printf("Argc_%d\n", cmd->argc);
	if (cmd->argv)
	{
		while (i < cmd->argc)
		{
			printf("ARGV[%d]_%s\n", i, cmd->argv[i]);
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
		printf("-- PRINT CUR CMD STRUCT --\n");
		if (cmd->builtin)
			printf("Builtin_%s\n", cmd->builtin);
		if (cmd->pipe)
			printf("Pipe_%s\n", cmd->pipe);
		if (cmd->tar_file)
			printf("Tar File_%s\n", cmd->tar_file);
		if (cmd->argc)
			printf("Argc_%d\n", cmd->argc);
		if (cmd->argv)
		{
			i = 0;
			while (i < cmd->argc)
			{
				printf("ARGV_%s\n",cmd->argv[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}
