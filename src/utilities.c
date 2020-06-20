/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:49 by greed         #+#    #+#                 */
/*   Updated: 2020/06/19 18:05:50 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_input(t_input *inp)
{
	if (inp->argv)
		fre_array(inp->argv);
	return ;
}

void	error_builtin(t_input *inp)
{
	int	i;

	i = 0;
	ft_printf_fd(2, "%s", inp->argv[i]);
	ft_printf_fd(2, "%s: ", strerror(errno));
	i += 1;
	while (inp->argc > 1)
	{
		if (inp->argc > 1)
		{
			printf(" ");
			i += 1;
			inp->argc -= 1;
		}
		else
		{
			printf("\n");
			return ;
		}
	}
	printf("\n");
}
