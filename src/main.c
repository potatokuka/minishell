/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/10/12 15:01:52 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */


int	main(void)
{
	t_data 	data;
	t_cmd	*head;

	ft_bzero(&data, sizeof(data));
	if (env_init(&data))
		put_error_data(&data, "Failed to parse env");
	set_signal();
	while (1)
	{
		print_prompt();
		parse_init(&data);
		head = data.cmd;
		while (data.cmd)
		{
			if (data.cmd->argc < 1 && !data.cmd->builtin)
			{
				dprintf(2, "syntax error near unexpected token ';'\n");
				break ;
			}
			// The leaks are all seemingly BEFORE this point.
			if (data.cmd->pipe_read_end != -1)
				fork_next_and_pipe(&data, data.cmd, 1);
			else
				cmd_dispatch(&data, data.cmd, 0);
			wait_for_children(&data.pid);
			if (data.cmd->next)
				update_env(&data);
			if (data.cmd->next)
				dprintf(2, "-- NEXT CMD --\n");
			data.cmd = data.cmd->next;
		}
		data.cmd = head;
		reset_data_struct(&data, 0);//TODO actually make this comprehensive reset
		update_env(&data);
	}
	return (0);
}
