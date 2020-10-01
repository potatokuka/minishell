/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set_val.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:29 by greed         #+#    #+#                 */
/*   Updated: 2020/10/01 15:05:39 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** move through the list of env's searching for if the EXPORT is existing, if it is, update
** the val for it, if not make one and set it
*/

void	env_set_val(const char *name, t_var **env, const char *val)
{
	t_var	*curr;
	t_var	*last;

	if (!*env)
	{
		*env = env_add(name, val);
		return ;
	}
	curr = *env;
	/*dprintf(2, "curr_%p_%p\nenv_%p\n", curr, curr->next, *env);*/
	last = curr;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			free(curr->val);
			curr->val = ft_strdup_lib(val);
			if (!curr->val)
				put_error("Failed to allocate");
			return ;
		}
		last = curr;
		curr = curr->next;
	}
	/*dprintf(2, "curr_%p\nenv_%p\n", curr, *env);*/
	/*dprintf(2,"\n\n ** - TESTING THIS SHIT - **\n\nname_%s\nval_%s\n\n", name, val);*/
	last->next = env_add(name, val);
	if (!last->next)
		put_error("Failed to allocate");
	/*dprintf(2,"\n\n ** - TESTING THIS SHIT B4 RETURN - **\n\nname_%s\nval_%s\n\n", name, val);*/
}
