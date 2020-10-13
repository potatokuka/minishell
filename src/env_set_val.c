/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set_val.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:29 by greed         #+#    #+#                 */
/*   Updated: 2020/10/08 11:50:09 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** move through the list of env's searching for if the EXPORT is existing, if it is, update
** the val for it, if not make one and set it
*/

int		env_set_val(const char *name, t_var **env, const char *val)
{
	t_var	*curr;
	t_var	*last;

	if (!*env)
	{
		*env = env_add(name, val);
		if (!*env)
			return (1);
		return (0);
	}
	curr = *env;
	last = curr;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->val);
			curr->val = ft_strdup_lib(val);
			if (!curr->val)
				return (1);
		}
		last = curr;
		curr = curr->next;
	}
	last->next = env_add(name, val);
	if (!last->next)
		return (1);
	return (0);
}
