/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:42:18 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/29 12:52:59 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_input *inp)
{
	int		i;

	i = 0;
	while (inp->envp[i])
	{
		ft_printf_fd(1, "%s\n", inp->envp[i]);
		i++;
	}
}
