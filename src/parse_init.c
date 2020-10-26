/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/26 13:12:48 by averheij      ########   odam.nl         */
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
	else if (ret == -1)
		put_error_data(data, "Invalid input read");
}

void	parse_init(t_data *data)
{
	char	*input_trimmed;
	int		ret;

	if (!data->input_leftovers)
	{
		ret = get_next_line(STDIN, &data->input_head);
		/*if (ret <= 0)*/
			parse_init2(data, ret);
		/*input_trimmed = trim_spaces(data->input_head);*/
		/*if (!*input_trimmed)*/
			/*return (free(data->input_head));*/
		if (parse_args(data, data->input_head))
			return (free(data->input_head));
	}
	else if (parse_args(data, data->input_leftovers))
		return (free(data->input_head));
	if (!data->input_leftovers)
		free(data->input_head);
	data->argv = list_to_string_array(data->arg_lst);
	data->argv_head = data->argv;
	free_list(data->arg_lst, free);
	data->arg_lst = NULL;
	if (!data->argv)
		put_error_data(data, "Failed to allocate 1");
	if (parse_organize(data))
		reset_data_struct(data, 0);
}
