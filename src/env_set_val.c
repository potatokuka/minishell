/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set_val.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:29 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 18:11:21 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_last(const char *name, t_var *curr, const char *val)
{
	if (ft_strcmp(curr->name, name) == 0)
	{
		free(curr->val);
		curr->val = ft_strdup_lib(val);
		dprintf(2,"\n\n ** - TESTING THIS SHIT - **\n\nname_%s\nval_%s\n\n", name, val);
		return (1);
	}
	dprintf(2,"\n\n ** - TESTING THIS SHIT - **\n\nname_%s\nval_%s\n\n", name, val);
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
		dprintf(2,"\n\n ** - TESTING THIS SHIT - **\n\nname_%s\nval_%s\n\n", name, val);
		*env = env_add(name, val);
		return (*env);
	}
	if (is_last(name, curr, val))
		return (curr->val ? curr : NULL);
	dprintf(2,"\n\n ** - TESTING THIS SHIT B4 RETURN - **\n\nname_%s\nval_%s\n\n", name, val);
	curr->next = env_add(name, val);
	return (curr->next);
}
