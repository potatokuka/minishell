/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 17:36:53 by greed         #+#    #+#                 */
/*   Updated: 2020/10/26 16:52:54 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			escset(char *input, char *set, int i)
{
	while (*set)
	{
		if (input[i] == *set && check_escape(input, i))
			return (1);
		set++;
	}
	return (0);
}

int			iscset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strljoin(char const *s1, ssize_t l1, char const *s2, ssize_t l2)
{
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	l1 = (l1 == -1) ? ft_strlen_lib(s1) : l1;
	l2 = (l2 == -1) ? ft_strlen_lib(s2) : l2;
	res = (char *)ft_calloc(sizeof(char), l1 + l2 + 1);
	if (!res)
		return (0);
	res[l1 + l2] = '\0';
	i = 0;
	while (i < l1 || i < l2)
	{
		if (i < l1)
			res[i] = s1[i];
		if (i < l2)
			res[i + l1] = s2[i];
		i++;
	}
	return (res);
}

int			add_arg(t_data *data, char *arg, char *input)
{
	if (!arg)
		return (1);
	if (iscset(*input, "><|;") && *arg == '\0')
	{
		free(arg);
		return (0);
	}
	data->argc += 1;
	if (!lst_new_back(&data->arg_lst, arg))
		put_error_data(data, "Failed to add to back of list");
	return (0);
}

char		*arg(t_data *dt, char *in, char *break_chars, int qt)
{
	int		i;
	char	*rt;

	i = 0;
	while (in[i] && !escset(in, break_chars, i))
	{
		if (!qt && (in[i] == D_QOTE || in[i] == S_QOTE)
				&& check_escape(in, i))
			return (safe_strljoin(in, i, arg(dt, in + i + 1, "", in[i]), dt));
		else if ((qt && in[i] == qt) && (qt == S_QOTE || check_escape(in, i)))
		{
			rt = handle_escapes_envs(dt, ft_strldup(in, i), qt, 1);
			if (!iscset(in[i + 1], "><|; "))
			{
				if (in[i + 1] == D_QOTE || in[i + 1] == S_QOTE)
					return (safestrjn(rt, arg(dt, in + i + 2, "", in[i + 1])));
				else
					return (safestrjn(rt, arg(dt, in + i + 1, "><|; ", 0)));
			}
			return (rt);
		}
		i++;
	}
	rt = handle_escapes_envs(dt, ft_strldup(in, i), '"', 1);
	return (rt);
}
