/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_prompt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 14:22:33 by greed         #+#    #+#                 */
/*   Updated: 2020/10/14 11:42:24 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(void)
{
	if (g_prompt_printed == 0)
		ft_printf_fd(2, "\e[1;34m%s\e[0m", PROMPT);
	g_prompt_printed = 1;
}
