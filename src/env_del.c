/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:11:11 by greed         #+#    #+#                 */
/*   Updated: 2020/06/24 14:00:05 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_del(t_var *delete)
{
	if (delete)
	{
		if (delete->name)
			free(delete->name);
		if (delete->val)
			free(delete->val);
		free(delete);
	}
}
