/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 17:36:53 by greed         #+#    #+#                 */
/*   Updated: 2020/10/16 14:15:16 by averheij      ########   odam.nl         */
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
	dprintf(2, "join_\t_%ld_%s\t_%ld_%s\n", l1, s1, l2, s2);
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

int			add_arg(t_data *data, char *arg)
{
	if (!arg)
		return (1);
	int i = 0;
	while (arg[i])
	{
		dprintf(2, "%c_", arg[i]);
		i++;
	}
	dprintf(2, "\n");
	if (*arg == '\0')
	{
		free(arg);
		return (0);
	}
	data->argc += 1;
	if (!lst_new_back(&data->arg_lst, arg))
		put_error_data(data, "Failed to add to back of list");
	return (0);
}

char		*safe_strljoin(char *s1, ssize_t l1, char *s2, ssize_t l2)
{
	char	*res;

	res = ft_strljoin(s1, l1, s2, l2);
	if (l1 == -1)
		free(s1);
	if (l2 == -1)
		free(s2);
	return (res);
}

char		*safe_strjoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char		*arg(t_data *dt, char *in, char *break_chars, int quote)
{
	int		i;
	char	*rt;

	i = 0;
	dprintf(2, "in__\t_%c\t_%s\n", quote, in);
	while (in[i] && !escset(in, break_chars, i))
	{
		if (!quote && (in[i] == D_QOTE || in[i] == S_QOTE)
				&& check_escape(in, i))
			return (safe_strljoin(in, i, arg(dt, in + i + 1, "", in[i]), -1));
		else if ((quote && in[i] == quote) && check_escape(in, i))
		{
			rt = handle_escapes_envs(dt, ft_strldup(in, i), quote, 1);
			if (!iscset(in[i + 1], "><|; "))
			{
				dprintf(2, "retq\t_%s\t_%s\n", rt, in);
				if (in[i + 1] == D_QOTE || in[i + 1] == S_QOTE)
					return (safe_strjoin(rt, arg(dt, in + i + 2, "", in[i + 1])));
				else
					return (safe_strjoin(rt, arg(dt, in + i + 1, "><|; ", 0)));
			}
			return (rt);
		}
		i++;
	}
	rt = handle_escapes_envs(dt, ft_strldup(in, i), 0, 0);
	dprintf(2, "rets\t_%s\t_%s\n", rt, in);
	return (rt);
}
