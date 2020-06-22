/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_del.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:11:11 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 23:11:12 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_del(t_var *delete)
{
	free(delete->name);
	free(delete->val);
	free(delete);
}
