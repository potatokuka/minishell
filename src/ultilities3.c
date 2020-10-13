/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 13:53:40 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 13:53:41 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_var(t_var *env)
{
	if (!env)
		return ;
	if (env->name)
		ft_free((void **)&env->name);
	if (env->val)
		ft_free((void **)&env->val);
	if (env->next && env->next != NULL)
		free_var(env->next);
	free(env);
}
