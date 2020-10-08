/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/08 16:09:17 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_init(t_data *data)
{
	char	*input_str;
	int		ret;

	ret = get_next_line(STDIN, &input_str); // freed - line 65 
	if (ret <= 0)
	{
		if (ret == 0)
		{
			ft_printf("exit\n");
			reset_data_struct(data, 1);
			exit(1);
		}
		else
			put_error_data(data, "Invalid input read");
	}
	input_str = trim_spaces(input_str);
	if (!*input_str)
		return ;
	if (parse_args(data, input_str))
		return ;
	data->argv = list_to_string_array(data->arg_lst);
	free(input_str);
	free_list(data->arg_lst, free);
	data->arg_lst = NULL;
	if (!data->argv)
		put_error_data(data, "Failed to allocate");
	if (parse_organize(data))
		put_error_data(data, "Failed to allocate");
}
