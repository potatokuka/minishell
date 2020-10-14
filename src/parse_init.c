/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/14 12:13:22 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_init2(t_data *data, int ret)
{
	if (ret == 0)
	{
		ft_printf("exit\n");
		reset_data_struct(data, 1);
		exit(0);
	}
	else
		put_error_data(data, "Invalid input read");
}

void	parse_init(t_data *data)
{
	char	*input_str;
	int		ret;

	ret = get_next_line(STDIN, &input_str);
	if (ret <= 0)
		parse_init2(data, ret);
	input_str = trim_spaces(input_str);
	if (!*input_str)
	{
		free(input_str);
		return ;
	}
	if (parse_args(data, input_str))
		return ;
	data->argv = list_to_string_array(data->arg_lst);
	free(input_str);
	free_list(data->arg_lst, free);
	data->arg_lst = NULL;
	if (!data->argv)
		put_error_data(data, "Failed to allocate 1");
	if (parse_organize(data))
		reset_data_struct(data, 0);
}
