/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_convert.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:38 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 14:38:36 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t		env_size(t_var *env)
{
	size_t len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char				**convert_env(t_var *env)
{
	size_t		i;
	size_t		len;
	char		**env_arr;

	i = 0;
	len = env_size(env);
	env_arr = ft_calloc(sizeof(char *), (len + 1));
	if (!env_arr)
		return (NULL);
	while (i < len)
	{
		env_arr[i] = ft_3strjoin(env->name, "=", env->val);
		if (!env_arr[i])
			return (free_array_null(env_arr));
		env = env->next;
		i++;
	}
	return (env_arr);
}
