/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/06/24 17:41:11 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Takes RES and returns a pointer to the next occurence of an alpha
*/

void	parse_input(t_input *inp, char *res)
{
	char	*trimmed;

	trimmed = del_leading_space(res);
	trimmed = parse_cmd(inp, trimmed);
	if (trimmed)
		parse_args(inp, trimmed, 0);
	split_arg_lst(inp);
}

void	parse_init(t_input *inp)
{
	char	*res;

	if (get_next_line(STDIN, &res) < 0)
		put_error("Invalid input read");
	parse_input(inp, res);
	free(res);
	free_list(inp->arg_lst, &free);
	print_vars(inp);
}
