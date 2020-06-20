/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 10:11:09 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 10:11:10 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_input *inp)
{
	(void)inp;
	printf("exiting from exit\n");
	exit (0);
}
