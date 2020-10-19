/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/10/19 15:04:39 by averheij      ########   odam.nl         */
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

char		*handle_escape_quotes(char *arg, char *escapeme)
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
		if ((arg[i] == '\\' && arg[i + 1] == '\\')
		|| (arg[i] == '\\' && iscset(arg[i + 1], "\"\'")))
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

char		*handle_escapes_envs(t_data *d, char *arg, int quote_type,
		int quote_flag)
{
	if (!arg)
		put_error_data(d, "Allocation Failed Quotes");
	arg = str_env_replace(d, arg, 1);
	if (!arg)
		put_error_data(d, "Failed to Allocate Quote");
	if (quote_type == D_QOTE)
	{
		arg = handle_escape_quotes(arg, "\"\'");
		if (!arg)
			put_error_data(d, "Failed to Allocate Quote");
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
		else if (in_quote && input[*i] == in_quote && (in_quote = S_QOTE || check_escape(input, *i)))
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
	if (iscset(input[i], "><|;"))
	{
		if (add_arg(data, ft_strldup(input + i, (input[i + 1] == '>') ? 2 : 1)))
			put_error_data(data, "Failed to allocate arg");
		i += (input[i + 1] == '>') ? 2 : 1;
	}
	if (input[i])
		return (parse_args(data, input + i));
	return (0);
}
