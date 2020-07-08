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
		redir_init(&inp);
		redir_dispatch(&inp);
		if (inp.cmd)
		{
			cmd_dispatch(inp.cmd, &inp.env, inp.envp);
			if (inp.cmd->update_env)
				update_env(&inp);
		}
		reset_input(&inp);
		/*ft_bzero(&inp, sizeof(inp));//TODO free argv, cmd, env*/
	}
	return (0);
}
