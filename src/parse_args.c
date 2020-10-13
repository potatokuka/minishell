/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 15:16:27 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** save until non alpha into args[i]
** IF read a Quote or Dquote send to save with quotes
** trim_spaces after each arg is saved
** maybe can do this recursively
** save everything from SP to SP, SP is 32 in ascii dec
** EASIER WAY, save each arg into linked list, split into array
** after it's fully finished
*/

bool		check_escape(char *str, int i)
{
	int		count;

	count = 0;
	if (i > 0)
	{
		i -= 1;
		while (i >= 0 && (str[i] == '\\'))
		{
			count += 1;
			i--;
		}
		if (count % 2 == 0)
			return (true);
		else
			return (false);
	}
	return (true);
}

char		*handle_escape_quotes(char *arg, int flag)
{
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = ft_calloc(ft_strlen_lib(arg), sizeof(char));
	if (!tmp)
		return (NULL);
	while (arg[i])
	{
		if ((arg[i] == '\\' && arg[i + 1] == '\\')
		|| (arg[i] == '\\' && arg[i + 1] == '\"' && flag == 1)
		|| (arg[i] == '\\'))
		{
			tmp[x] = arg[i + 1];
			i++;
		}
		else
			tmp[x] = arg[i];
		i++;
		x++;
	}
	free(arg);
	return (tmp);
}

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

char		*ft_strljoin(char const *s1, size_t l1, char const *s2, size_t l2)
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

int			add_arg(t_data *data, char *arg)
{
	if (!arg)
		return (1);
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

static char	*handle_escapes_envs(t_data *d, char *arg, int quote_type,
		int quote_flag)
{
	if (!arg)
		put_error_data(d, "Allocation Failed Quotes");
	arg = str_env_replace(d, arg, 1);
	if (!arg)
		put_error_data(d, "Failed to Allocate Quote");
	if (quote_type == D_QOTE)
	{
		arg = handle_escape_quotes(arg, quote_flag);
		if (!arg)
			put_error_data(d, "Failed to Allocate Quote");
	}
	return (arg);
}

char		*arg(t_data *dt, char *in, char *break_chars, int quote)
{
	int		i;
	char	*rt;

	i = 0;
	while (in[i] && !escset(in, break_chars, i))
	{
		/*dprintf(2, "%d_%c_%s\n", i, in[i], in);*/
		if (!quote && (in[i] == D_QOTE || in[i] == S_QOTE)
				&& check_escape(in, i))
			return (ft_strljoin(in, i, arg(dt, in + i + 1, "", in[i]), -1));
		else if ((quote && in[i] == quote) && check_escape(in, i))
		{
			rt = handle_escapes_envs(dt, ft_strldup(in, i), quote, 1);
			if (!iscset(in[i + 1], "><|; "))
			{
				if (in[i + 1] == D_QOTE || in[i] == S_QOTE)
					return (ft_strjoin(rt, arg(dt, in + i + 2, "", in[i + 1])));
				else
					return (ft_strjoin(rt, arg(dt, in + i + 1, "><|; ", 0)));
			}
			return (rt);
		}
		i++;
	}
	rt = handle_escapes_envs(dt, ft_strldup(in, i), 0, 0);
	return (rt);
}

static int	check_quotes_closed(char *input, int *i)
{
	int		in_quote;

	in_quote = 0;
	*i = 0;
	while (input[*i] && (in_quote || !escset(input, "><|; ", *i)))
	{
		if (!in_quote && (input[*i] == D_QOTE || input[*i] == S_QOTE)
				&& check_escape(input, *i))
			in_quote = input[*i];
		else if (in_quote && input[*i] == in_quote && check_escape(input, *i))
			in_quote = 0;
		(*i)++;
	}
	return (in_quote);
}

int			parse_args(t_data *data, char *input)
{
	int		i;

	if (!input)
		return (1);
	input = trim_spaces(input);
	if (*input)
		if (add_arg(data, arg(data, input, "><|; ", 0)))
			put_error_data(data, "Failed to allocate arg");
	if (check_quotes_closed(input, &i))
		return (reset_prompt(data, "Unclosed quotes", 1, 0));
	/*dprintf(2, "before recall %s\n", input + i);*/
	if (iscset(input[i], "><|;"))
	{
		if (add_arg(data, ft_strldup(input + i, (input[i + 1] == '>') ? 2 : 1)))
			put_error_data(data, "Failed to allocate arg");
		i += (input[i + 1] == '>') ? 2 : 1;
	}
	/*dprintf(2, "before recall %s\n", input + i);*/
	if (input[i])
		return (parse_args(data, input + i));
	return (0);
}
