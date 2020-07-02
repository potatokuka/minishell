/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_organize.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/07/02 16:56:48 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
*/

void	parse_organize(t_input *inp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < inp->argc)
	{

	}
}
