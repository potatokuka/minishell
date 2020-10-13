/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 17:29:32 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 17:30:56 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*convert_esc2(char *arg, char *tmp, int i, int x)
{
	char	*res;

	while (arg[i])
	{
		dprintf(2, "testing arg[i] %c\n", arg[i]);
		if (arg[i] == '\\')
		{
			dprintf(2, "arg check again %s char %c\n", arg, arg[i]);
			tmp[x] = arg[i + 1];
			i += 2;
			x++;
		}
		else
		{
			tmp[x] = arg[i];
			x++;
			i++;
		}
	}
	res = ft_strldup(tmp, x);
	free(tmp);
	return (res);
}

int				has_escape(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

void			convert_esc(t_data *data, t_cmd *new, char *arg, int index)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	dprintf(2, "Arg= %s\n", arg);
	tmp = ft_calloc(ft_strlen_lib(arg), sizeof(char));
	if (!tmp)
		put_error_data(data, "Allocation Failed 2");
	ret = convert_esc2(arg, tmp, i, x);
	if (!ret)
		put_error_data(data, "Allocation Failed !");
	dprintf(2, "Test RET_%s\n", ret);
	if (!lst_new_back(&new->arr_list, ft_strdup(ret)))
		put_error_data(data, "Failed Allocation in lst back Parse Re");
	free(tmp);
	new->argc += 1;
	data->argc -= 1;
	drop_string(data, index);
}
