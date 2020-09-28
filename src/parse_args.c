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

bool	check_escape(char *str, int i)
{
	// TRUE, BREAK STRING HERE EVEN == GTFO
	// FALSE, ESCAPE IT. ODD == ESCAPE
	// go from this point, backwards while i > 0
	// count consecutive '\\' in a row
	// while ('\\')
	int		count;

	count = 0;
	if (i > 0)
	{
		i -= 1;
		while (i > 0 && (str[i] == '\\'))
		{
			count += 1;
			i--;
		}
		if (count % 2 == 0)
		{
			dprintf(2, "%d mod 2 : TRUE\n", count);
			return (true);
		}
		else
		{

			dprintf(2, "%d mod 2 : FALSE\n", count);
			return (false);
		}
	}
	return (true);
	/* if (i > 1 && str[i - 2] == '\\' && str[i - 1] == '\\') */
	/* 	return (true); */
	/* else if (i > 0 && (str[i - 1] == '\\')) */
	/* 	return (false); */
	/* else */
	/* 	return (true); */
}

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
		if (arg[i] == '\\' && arg[i + 1] == '\\')
		{
			dprintf(2, "arg check again %s char %c\n", arg, arg[i]);
			tmp[x] = arg[i + 1];
			i += 2;
			x++;
		}
		else if (arg[i] == '\\' && arg[i + 1] == '\"')
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
	ret = ft_strldup(tmp, x);
	free(tmp);
	dprintf(2, "Test RET_%s\n", ret);
	return (ret);
}

int		escset(char *input, char *set, int i)
{
	while (*set)
	{
		if (input[i] == *set && check_escape(input, i))
			return (1);
		set++;
	}
	return (0);
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
	while (input[i] && !escset(input, break_chars, i))
	{
		/*printf("%d %c\n", i, input[i]);*/
		/* dprintf(2, "this, is check : %s\n", input); */
		if (!quote && (input[i] == D_QOTE || input[i] == S_QOTE))
			return (ft_strljoin(input, i, parse_arg(d, input + i + 1, "", input[i]), -1));//Leaks
		else if ((quote && input[i] == quote) && check_escape(input, i))
		{
			arg = ft_strldup(input, i);
			dprintf(2, "testing arg %s\n", arg);
			if (quote == D_QOTE)
			{
				arg = handle_escape_quotes(arg);
				dprintf(2, "testing char %c %c arg = %s\n", input[i - 1], input[i], arg);
				arg = str_env_replace(d, arg, 1);
			}
			if (!iscset(input[i + 1], "><|; "))
			{

				dprintf(2, "iscest being returned : %s\n", arg);
				if (input[i + 1] == D_QOTE || input[i] == S_QOTE)
					return (ft_strjoin(arg, parse_arg(d, input + i + 2, "", input[i + 1])));//Leaks
				else
					return (ft_strjoin(arg, parse_arg(d, input + i + 1, "><|; ", 0)));//Leaks
			}
			dprintf(2, "Arg being returned : %s\n", arg);
			return (arg);
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
	dprintf(2, "Testing input before first WHILE: %s\n", input);
	while (input[i] && (in_quote || !escset(input, "><|; ", i)))
	{
		if (!in_quote && (input[i] == D_QOTE || input[i] == S_QOTE))
			in_quote = input[i];
		else if (in_quote && input[i] == in_quote && check_escape(input, i))
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

