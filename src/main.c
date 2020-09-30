/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 15:32:26 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */


int	main(void)
{
	t_data data;
	int		times = 1;
	ft_bzero(&data, sizeof(data));
	if (env_init(&data))
		put_error("Failed to parse env");
	set_signal();
	while (1)
	{
		print_prompt();
		parse_init(&data);
		while (data.cmd)
		{
			if (data.cmd->argc < 1 && !data.cmd->builtin)
			{
				dprintf(2, "syntax error near unexpected token ';'\n");
				break ;
			}
			if (data.cmd->pipe_read_end != -1)
				fork_next_and_pipe(data.cmd, &data.env, data.envp, &data.pid, &data.fd, 1);
			else
				cmd_dispatch(data.cmd, &data.env, data.envp, &data.pid);
			if (data.cmd->update_env)
				update_env(&data);
			if (data.cmd->next)
				dprintf(2, "-- NEXT CMD --\n");
			data.cmd = data.cmd->next;
		}
		reset_data(&data);//TODO actually make this comprehensive reset
	}
	return (0);
}
