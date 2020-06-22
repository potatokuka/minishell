/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:24 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 23:10:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** read through list of structs for the sent STR(name of ENV)
** if it is found kill that shit loop through the whole list
*/

void		unset_env(t_var **env, char *str)
{
	t_var	*curr;
	t_var	*prev;

	curr = *env;
	prev = curr;
	if (!*env)
		return ;
	if (ft_strcmp(str, (*env)->name) == 0)
	{
		*env = (*env)->next;
		env_del(curr);
		return ;
	}
	while (curr)
	{
		if (ft_strcmp(str, curr->name) == 0)
		{
			prev->next = curr->next;
			env_del(curr);
			curr = prev;
		}
		prev = curr;
		curr = curr->next;
	}
}
