/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/07/14 19:45:30 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Takes RES and returns a pointer to the next occurence of an alpha
*/

void	parse_input(t_data *data, char *input_str)
{
	input_str = trim_spaces(input_str);
	if (input_str)
		parse_args(data, input_str);
	data->argv = list_to_string_array(data->arg_lst);
	subtitute_enviroment_variables(data);
}

void	parse_init(t_data *data)
{
	char	*input_str;
	int		ret;

	ret = (get_next_line(STDIN, &input_str));
	if (ret <= 0)
	{
		if (ret == 0)
		{
			ft_printf("exit\n");
			exit(1);
		}
		else
			put_error("Invalid input read");
	}
	parse_input(data, input_str);
	free(input_str);
	free_list(data->arg_lst, &free);
	parse_organize(data);
	print_vars(data);
}
