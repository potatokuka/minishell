/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:44 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 23:10:45 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*env_add(const char *name, const char *val)
{
	t_var	*add;
	
	add = malloc(sizeof(t_var));
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
