/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 13:43:46 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 13:43:51 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** send each argv to get removed from ENV if they exist 
*/

void		ft_unset(t_input *inp)
{
	int		i;

	if (inp->argc < 1)
		return ;
	i = 0;
	while (inp->argv[i])
	{
		unset_env(&inp->env, inp->argv[i]);
		i++;
	}
	update_env(inp);
}
