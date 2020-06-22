/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clear.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 17:41:46 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 15:11:51 by greed         ########   odam.nl         */
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
		del(delete->name);
		del(delete->val);
	}
	return (0);
}
