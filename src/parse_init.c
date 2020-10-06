/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/05 14:47:51 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_escape_quotes(char *str)
{
	int		i;
	int		x;
	char	*tmp;
	char	*ret;
	int		in_quote;

	i = 0;
	x = 0;
	in_quote = 0;
	tmp = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			i += 1;
		}
		tmp[x] = str[i];
		i++;
		x++;
	}
	ret = ft_strldup(tmp, x);
	free(tmp);
	return(ret);
}

void	parse_init(t_data *data)
{
	char	*input_str;
	int		ret;

	ret = get_next_line(STDIN, &input_str);
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
	if (parse_args(data, input_str))
		return ;
	data->argv = list_to_string_array(data->arg_lst);
	free(input_str);
	free_list(data->arg_lst, &free);
	data->arg_lst = NULL;
	if (!data->argv)
		put_error("Failed to allocate");
	if (parse_organize(data))
		put_error("Failed to allocate");
}
