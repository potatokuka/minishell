/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 17:41:46 by greed         #+#    #+#                 */
/*   Updated: 2020/06/24 13:41:52 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		clear_env(t_var *env, void(*del)(void *))
{
	t_var	*delete;

	while (env)
	{
		delete = env;
		env = env->next;
		if (delete->name)
			del(delete->name);
		if (delete->val)
			del(delete->val);
	}
	return (0);
}
