/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:44 by greed         #+#    #+#                 */
/*   Updated: 2020/10/01 15:09:10 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*env_add(const char *name, const char *val)
{
	t_var	*add;

	add = ft_calloc(1, sizeof(t_var));
	if (!add)
		return (NULL);
	add->len = (ft_strlen_lib(name) + (ft_strlen_lib(val) + 1));
	add->name = ft_strdup_lib(name);
	if (!add->name)
		return (NULL);
	add->val = ft_strdup_lib(val);
	if (!add->val)
		return (NULL);
	add->next = NULL;
	return (add);
}

void	set_exit_env_val(t_var **env, int *last_status)
{
	char	*status;

	status = ft_itoa(*last_status);
	env_set_val("?", env, status);
	free(status);
	*last_status = 0;
}
