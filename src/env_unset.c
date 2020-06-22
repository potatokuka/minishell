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
	last = curr;
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
			last->next = curr->next;
			env_del(curr);
			curr = last;
		}
		last = curr;
		curr = curr->next;
	}
}
