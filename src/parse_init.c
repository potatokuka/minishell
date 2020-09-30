/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 12:32:09 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	input_str = trim_spaces(input_str);
	if (!*input_str)
		return ;
	parse_args(data, input_str);
	data->argv = list_to_string_array(data->arg_lst);
	free(input_str);
	free_list(data->arg_lst, &free);
	parse_organize(data);
	/*print_vars(data);*/
}
