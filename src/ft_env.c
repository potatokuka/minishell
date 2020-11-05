/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 12:42:18 by averheij      #+#    #+#                 */
/*   Updated: 2020/11/05 15:18:07 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp, char *prestr)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] != '?')
			ft_printf_fd(1, "%s%s\n", prestr, envp[i]);
		i++;
	}
}
