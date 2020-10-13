/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/18 13:39:53 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/02 14:58:20 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_quit(int i)
{
	g_signal_exit = i;
	ft_printf_fd(2, "\n");
	return ;
}

void	sig_handler_int(int i)
{
	g_signal_exit = i;
	ft_printf_fd(2, "\n");
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, sig_handler_quit);
	signal(SIGINT, sig_handler_int);
	g_signal_exit = 0;
}
