/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 17:01:56 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */

int	main(void)
{
	t_data data;

	ft_bzero(&data, sizeof(data));
	if (env_init(&data))
		put_error("Failed to parse env");
	/*set_signal();*/
	while (1)
	{
		print_prompt();
		parse_init(&data);
		while (data.cmd)
		{
			redir_dispatch(&data);
			cmd_dispatch(data.cmd, &data.env, data.envp);
			if (data.cmd->update_env)
				update_env(&data);
			if (data.cmd->pipe && data.cmd->pid1 == 0)
				exit (1);
			data.cmd = data.cmd->next;
		}
		reset_data(&data);//TODO actually make this comprehensive reset
	}
	return (0);
}
