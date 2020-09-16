/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/07/08 18:37:49 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */

int	main(void)
{
	t_data data;

	ft_bzero(&data, sizeof(data));
	env_init(&data);
	set_signal();
	while (1)
	{
		print_prompt();
		parse_init(&data);
		// TODO make this a while_loop while imp.cmd and move im.cmd->next at
		// bottom
		while (data.cmd)
		{
			redir_dispatch(&data);
			cmd_dispatch(data.cmd, &data.env, data.envp);
			if (data.cmd->update_env)
				update_env(&data);
			if (data.cmd->pipe && data.cmd->pid1 == 0)
				exit (1);
			/* if (data.cmd->next) */
			data.cmd = data.cmd->next;
		}
		reset_data(&data);
		/*ft_bzero(&data, sizeof(data));//TODO free argv, cmd, env*/
	}
	return (0);
}
