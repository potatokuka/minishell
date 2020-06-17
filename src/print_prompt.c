/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_out.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 14:22:33 by greed         #+#    #+#                 */
/*   Updated: 2020/06/15 14:45:36 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(t_input *inp)
{
  (void)inp;
  ft_printf("\e[1;34m%s\e[0m", PROMPT);
}
