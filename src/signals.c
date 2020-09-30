/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/18 13:39:53 by averheij      #+#    #+#                 */
/*   Updated: 2020/09/28 11:15:15 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_inp(int i)
{
	(void)i;
	ft_printf_fd(2, "\n");
	print_prompt();
	return ;
}
void	sig_handler(int i)
{
	(void)i;
	ft_printf_fd(2, "\n");
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, sig_handler_inp);
	signal(SIGINT, sig_handler_inp);
	/*signal(SIGSTOP, sig_handler_inp);*/
}
