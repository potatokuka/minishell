/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:42:18 by averheij      #+#    #+#                 */
/*   Updated: 2020/07/06 13:13:30 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_printf_fd(1, "%s\n", envp[i]);
		i++;
	}
}
