/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 17:46:06 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** save until non alpha into args[i]
** IF read a Quote or Dquote send to save with quotes
** trim_spaces after each arg is saved
** maybe can do this recursively
** save everything from SP to SP, SP is 32 in ascii dec
** EASIER WAY, save each arg into linked list, split into array
** after it's fully finished
*/

void	parse_args(t_data *data, char *trimmed)
{
	char	*str;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	trimmed = trim_spaces(trimmed);
	ft_printf_fd(2, "remaining string_%s\n", trimmed);
	if (*trimmed == D_QOTE || *trimmed == S_QOTE)
		trimmed = ft_save_literal(data, (trimmed + 1), 0, *trimmed, trimmed);
	else
	{
		str = ft_strldup(trimmed, ft_strchr_lib(trimmed, ' ') - trimmed);
		if (!str)
			put_error("Error in argument parsing");
		if (*str)
		{
			data->argc += 1;
			lst_new_back(&data->arg_lst, str);
		}
		trimmed = trimmed + ft_strlen_lib(str);
	}
	if (*trimmed)
		parse_args(data, trimmed);
}
