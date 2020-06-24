/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/06/24 16:37:10 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */

int	main(void)
{
	t_input inp;

	ft_bzero(&inp, sizeof(inp));
	/* env_init(&inp); */
	while (1)
	{
		env_init(&inp);
		print_prompt(&inp);
		parse_init(&inp);
		cmd_dispatch(&inp);
		/* reset_input(&inp); */
		ft_bzero(&inp, sizeof(inp));//TODO free argv, cmd, env
		//Maybe we should split env into a different struct, so that we can just bzero input and not re parse in all of env every command
	}
	return (0);
}
