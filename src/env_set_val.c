/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set_val.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:29 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 23:10:30 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_last(const char *name, t_var *curr, const char *val)
{
	if (strcmp(curr->name, name) == 0)
	{
		free(curr->val);
		curr->val = ft_strdup_lib(val);
		return (1);
	}
	return (0);
}

/*
** move through the list of env's searching for if the EXPORT is existing, if it is, update
** the val for it, if not make one and set it
*/

t_var	*env_set_val(const char *name, t_var **env, const char *val)
{
	t_var	*curr;

	curr = *env;
	while (curr && curr->next)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->val);
			curr->val = ft_strdup_lib(val);
			if (!curr->val)
				return (NULL);
			return (curr);
		}
		curr = curr->next;
	}
	if (curr == *env)
	{
		*env = env_add(name, val);
		return (*env);
	}
	if (is_last(name, curr, val))
		return (curr);
	else
		return (NULL);
	curr->next = env_add(name, val);
	return (curr->next);
}
