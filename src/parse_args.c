/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/09/23 13:26:02 by averheij      ########   odam.nl         */
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

char	*handle_escape_quotes(char *arg)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	dprintf(2, "Arg= %s\n", arg);
	tmp = ft_calloc(ft_strlen_lib(arg), sizeof(char));
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		tmp[x] = arg[i];
		x++;
		i++;
	}
	ret = ft_strldup(tmp, x);
	free(tmp);
	dprintf(2, "Test RET_%s\n", ret);
	return (ret);
}

int		iscset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strljoin(char const *s1, size_t l1, char const *s2, size_t l2)
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


int		add_arg(t_data *data, char *arg)
{
	/*dprintf(2, "%s\n", arg);*/
	if (!arg)
		return (1);
	if (*arg == '\0')
	{
		free (arg);
		return (0);
	}
	data->argc += 1;
	lst_new_back(&data->arg_lst, arg);
	return (0);
}

char	*parse_arg(t_data *d, char *input, char *break_chars, int quote)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = 0;
	while (input[i] && !iscset(input[i], break_chars))
	{
		/*printf("%d %c\n", i, input[i]);*/
		if (!quote && (input[i] == D_QOTE || input[i] == S_QOTE))
			return (ft_strljoin(input, i, parse_arg(d, input + i + 1, "", input[i]), -1));//Leaks
		else if (quote && input[i] == quote && (quote == S_QOTE || (i > 0 && input[i - 1] != '\\')))
		{
			arg = ft_strldup(input, i);
			dprintf(2, "testing arg %s\n", arg);
			if (quote == D_QOTE)
			{
				arg = handle_escape_quotes(arg);
				dprintf(2, "testing char %c %c\n", input[i - 1], input[i]);
				arg = str_env_replace(d, arg, 1);
			}
			if (!iscset(input[i + 1], "><|; "))
			{
				if (input[i + 1] == D_QOTE || input[i] == S_QOTE)
					return (ft_strjoin(arg, parse_arg(d, input + i + 2, "", input[i + 1])));//Leaks
				else
					return (ft_strjoin(arg, parse_arg(d, input + i + 1, "><|; ", 0)));//Leaks
			}
			return (arg);
		}
		else if (i > 0 && input[i] == '\\')
		{
			if (input[i] == '\\' && input[i + 1] == '\"')
			{

			}
		}
		i++;
	}
	dprintf(2, "134 check : %s\n", input);
	return (ft_strldup(input, i));
}

int		parse_args(t_data *data, char *input)
{
	char	*input_head;
	int		i;
	int		in_quote;

	if (!input)
		return (1);
	input = trim_spaces(input);
	/*ft_printf_fd(2, "remaining string_%s\n", input);*/
	if (*input)
		if (add_arg(data, parse_arg(data, input, "><|; ", 0)))
			put_error("Failed to parse input");
	i = 0;
	in_quote = 0;
	while (input[i] && (in_quote || !iscset(input[i], "><|; ")))
	{
		if (!in_quote && (input[i] == D_QOTE || input[i] == S_QOTE))
			in_quote = input[i];
		else if (in_quote && input[i] == in_quote && (in_quote == S_QOTE || (i > 0 && input[i - 1] != '\\')))
			in_quote = 0;
		i++;
	}
	if (in_quote)
		put_error("Unclosed quotes");//Instead of throwing error, clear any parsing and join a new input string with current string
	if (iscset(input[i], "><|;"))
	{
		add_arg(data, ft_strldup(input + i, (input[i + 1] == '>') ? 2 : 1));
		i += (input[i + 1] == '>') ? 2 : 1;
	}
	if (input[i])
		return(parse_args(data, input + i));
	return (0);
}

