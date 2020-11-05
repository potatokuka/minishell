/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/11/05 15:46:01 by averheij      ########   odam.nl         */
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

char		*handle_escape_quotes(char *arg, int type)
{
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = ft_calloc(ft_strlen_lib(arg) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (arg[i])
	{
		if ((type != 1 && iscset(arg[i + 1], "\0;<>|")) && arg[i] == '\\')
			return (free_ret_null(tmp, arg));
		else if (check_backslash(arg[i], arg[i + 1], type))
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

char		*handle_escapes_envs(t_data *da, char *arg, int substitute, int no_quote)
{
	if (no_quote == 0)
		da->had_quote = 1;
	if (!arg)
		put_error_data(da, "Allocation Failed Quotes");
	if (substitute && substitute != S_QOTE)
	{
		arg = str_env_replace(da, arg, substitute);
		if (!arg)
			put_error_data(da, "Failed to Allocate Quote");
		arg = handle_escape_quotes(arg, substitute);
		if (!arg)
			put_error_data(da, "Escape Char");
	}
	return (arg);
}

int			check_quotes_closed(char *input, int *i)
{
	int		in_quote;

	in_quote = 0;
	*i = 0;
	while (input[*i] && (in_quote || !escset(input, "><|; ", *i)))
	{
		if (!in_quote && (input[*i] == D_QOTE || input[*i] == S_QOTE)
				&& check_escape(input, *i))
			in_quote = input[*i];
		else if (in_quote && input[*i] == in_quote
				&& (in_quote == S_QOTE || check_escape(input, *i)))
			in_quote = 0;
		(*i)++;
	}
	return (in_quote);
}

int			parse_args(t_data *data, char *in)
{
	int		i;

	if (!in)
		return (1);
	in = trim_spaces(in);
	if (*in && add_arg(data, arg(data, in, "><|; ", 0), in))
		put_error_data(data, "Failed to allocate arg");
	if (check_quotes_closed(in, &i))
		return (reset_prompt(data, "Unclosed quotes", 2, 0));
	if (iscset(in[i], "><|"))
	{
		if (add_arg(data, ft_strldup(in + i, (in[i + 1] == '>') ? 2 : 1), in))
			put_error_data(data, "Failed to allocate arg");
		i += (in[i + 1] == '>') ? 2 : 1;
	}
	else if (in[i] == ';')
	{
		data->input_leftovers = in + i + 1;
		return (0);
	}
	if (in[i])
		return (parse_args(data, in + i));
	else
		data->input_leftovers = NULL;
	return (0);
}
