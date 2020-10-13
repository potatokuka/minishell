/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 17:41:28 by greed         #+#    #+#                 */
/*   Updated: 2020/10/12 13:13:31 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** stores the NAME of each ENV to be able to search through
** return	-	new string of name preceding =
**				char **str incremented to char after =
*/

static char		*var_name(char **str)
{
	char	*new;
	char	*end_point;
	size_t	i;

	i = 0;
	end_point = ft_strchr_lib(*str, '=');
	if (!end_point)
		return (NULL);
	new = ft_calloc(sizeof(char), ((end_point - *str) + 1));
	if (!new)
		return (NULL);
	while (**str && *str < end_point)
	{
		new[i] = **str;
		(*str)++;
		i++;
	}
	(*str)++;
	return (new);
}

static t_var	*var_init(char *str)
{
	t_var	*new;

	new = ft_calloc(sizeof(t_var), 1);
	if (!new)
		return (NULL);
	new->len = ft_strlen_lib(str);
	new->name = var_name(&str);
	if (!new->name)
		return (NULL);
	new->val = ft_strdup(str);
	if (!new->val)
	{
		free(new->name);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

/*
** sets the had of the env, stores for later and sets to -1 to make
** sure you only run this portion 1 time
*/

static int		env_head_init(t_data *data, char **environ)
{
	data->env = NULL;
	if (!environ || !environ[0])
		return (0);
	data->env = var_init(environ[0]);
	if (!data->env)
		return (clear_env(data->env, &free));
	return (0);
}

/*
** stores a shit load of values(VAL) for each ENV in seperate structs
*/

int				env_init(t_data *data)
{
	extern char **environ;
	t_var		*env;
	int			i;

	if (env_head_init(data, environ))
		return (1);
	i = 1;
	env = data->env;
	while (environ[i])
	{
		env->next = var_init(environ[i]);
		if (!env->next)
			return (clear_env(data->env, &free));
		env = env->next;
		i++;
	}
	i = 0;
	if (set_exit_env_val(&data->env, &i))
		return (clear_env(data->env, &free));
	data->envp = convert_env(data->env);
	if (!data->envp)
		return (clear_env(data->env, &free));
	return (0);
}
