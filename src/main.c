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
	t_input inp;

	ft_bzero(&inp, sizeof(inp));
	env_init(&inp);
	while (1)
	{
		print_prompt(&inp);
		parse_init(&inp);
		// TODO make this a while_loop while imp.cmd and move im.cmd->next at
		// bottom
		if (inp.cmd)
		{
			redir_dispatch(&inp);
			cmd_dispatch(inp.cmd, &inp.env, inp.envp);
			if (inp.cmd->update_env)
				update_env(&inp);
			if (inp.cmd->pipe && inp.cmd->pid1 == 0)
				exit (1);
			if (inp.cmd->next)
				inp.cmd = imp.cmd->next;
		}
		reset_input(&inp);
		/*ft_bzero(&inp, sizeof(inp));//TODO free argv, cmd, env*/
	}
	return (0);
}
