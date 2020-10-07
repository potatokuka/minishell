/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_error_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 12:44:22 by greed         #+#    #+#                 */
/*   Updated: 2020/10/07 12:44:23 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_data(t_data *data, char *error)
{
	reset_data_struct(data, 1);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
