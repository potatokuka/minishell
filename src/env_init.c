/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 17:41:28 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 20:57:47 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** stores the NAME of each ENV to be able to search through
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
	new = malloc(sizeof(char) * ((end_point - *str) + 1));
	if (!new)
		return (NULL);
	while (**str && *str < end_point)
	{
		new[i] = **str;
		(*str)++;
		i++;
	}
	new[i] = 0;
	(*str)++;
	return (new);
}

static t_var	*var_init(char *str)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->len = ft_strlen_lib(str);
	new->name = var_name(&str);
	if (!new->name)
		return (NULL);
	new->val = ft_strdup(str);
	if (!new->val)
		return (NULL);
	new->next = NULL;
	return (new);
}

/*
** sets the had of the env, stores for later and sets to -1 to make
** sure you only run this portion 1 time
*/
static int		env_head_init(t_input *inp, char **environ)
{
	inp->env = NULL;
	if (!environ || !environ[0])
		return (1);
	inp->env = var_init(environ[0]);
	if (!inp->env)
		return (clear_env(inp->env, &free));
	return (-1);
}

/*
** stores a shit load of values(VAL) for each ENV in seperate structs
*/ 

int				env_init(t_input *inp)
{
	extern char **environ;
	t_var		*env;
	int			i;

	i = env_head_init(inp, environ);
	if (i != -1)
		return (i);
	i = 1;
	env = inp->env;
	while (environ[i])
	{
		env->next = var_init(environ[i]);
		if (!env->next)
			return (clear_env(inp->env, &free));
		env = env->next;
		i++;
	}
	inp->envp = convert_env(inp->env);
	if (!inp->envp)
	{
		perror("env init");
		return (clear_env(inp->env, &free));
	}	
	return (1);
}
