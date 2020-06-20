/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 14:27:06 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 17:41:34 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(const char *name, t_var *env, size_t len)
{
	printf("get env check\n%s\n", env->name);
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0)
		{
			if (ft_strlen(env->name) == len)
				return (env->val);
		}
		env = env->next;
	}
	return (NULL);
}
