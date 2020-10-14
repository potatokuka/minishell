/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/14 12:56:10 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		clear_cmd(t_cmd **cmd)
{
	free_cmd(*cmd);
	*cmd = NULL;
	return (1);
}

int		drop_string(t_data *data, int i)
{
	if (data->argv[i])
		free(data->argv[i]);
	data->argv[i] = NULL;
	return (0);
}
