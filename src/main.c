/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/10/26 13:14:32 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		shell(t_data *data, t_cmd *head)
{
	if (!data->input_leftovers)
		print_prompt();
	g_prompt_printed = 0;
	parse_init(data);
	head = data->cmd;
	while (data->cmd)
	{
		if (data->cmd->argc < 1 && !data->cmd->builtin)
		{
			ft_printf_fd(2, "syntax error near unexpected token ';'\n");
			break ;
		}
		if (data->cmd->pipe_read_end != -1)
			fork_next_and_pipe(data, data->cmd, 1);
		else
			cmd_dispatch(data, data->cmd, 0);
		wait_for_children(&data->pid);
		if (data->cmd->next)
			update_env(data);
		data->cmd = data->cmd->next;
	}
	data->cmd = head;
	reset_data_struct(data, 0);
	update_env(data);
}

int				main(void)
{
	t_data	data;
	t_cmd	*head;

	head = NULL;
	g_is_parent = 1;
	ft_bzero(&data, sizeof(data));
	if (env_init(&data))
		put_error_data(&data, "Failed to parse env");
	set_signal();
	while (1)
		shell(&data, head);
	return (0);
}
