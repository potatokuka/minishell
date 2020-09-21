/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/09/21 17:19:53 by averheij      ########   odam.nl         */
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

char	*ft_save_flags(t_data *data, char *str, char flag)
{
	int		i;
	char	*tmp;
	int		end;

	i = 0;
	end = 0;
	dprintf(2, "testing new FLAG save %s\n", str);
	if (str[0] == '>' && str[1] == '>')
	{
		tmp = ft_strldup(str, 2);
		if (!tmp)
			put_error("Error in Arg Parsing FLAG");
		if (*tmp)
		{
			data->argc += 1;
			lst_new_back(&data->arg_lst, tmp);
		}
		str += 2;
	}
	else
	{
		tmp = ft_strldup(str, 1);
		if (!tmp)
			put_error("Error in Arg Parsing FLAG");
		if (*tmp)
		{
			data->argc += 1;
			lst_new_back(&data->arg_lst, tmp);
		}
		str += 1;
	}
	return (str);
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

void	add_arg(t_data *data, char **trimmed, int *i)
{
	char *str;

	str = ft_strldup(*trimmed, *i);
	if (!str)
		put_error("Error in arg parsing");
	data->argc += 1;
	str = str_env_replace(data, str, 1);
	lst_new_back(&data->arg_lst, str);
	*trimmed += *i;
	*i = 0;
}

void	add_string(t_data *data, char **trimmed, char quote)
{
	// save the string from the start of trimmed to i on stack,
	// save inside of the quotes, if a DOUBLE Quote, save inside of quotes and
	// check for valid ENV check, if Single Quote just save letter for letter
	// inside.
	char	*quote_str;
	int		q_count;
	int		len;
	int		start;

	q_count = 1;
	len = 0;
	while (q_count < 2 && (*trimmed)[1 + len])
	{
		if ((*trimmed)[1 + len] == quote)
			q_count += 1;
		len++;
	}
	if (q_count != 2)
		put_error("Your Quotes are shit mate.");
	quote_str = ft_strldup((*trimmed) + 1, len - 1);
	if (quote == D_QOTE)
		quote_str = str_env_replace(data, quote_str, 1);
	start = 1 + len;
	len = 0;
	while ((*trimmed)[start + len] && !iscset((*trimmed)[start + len], "><|; '\""))
		len++;
	quote_str = ft_strjoin(quote_str, ft_strldup((*trimmed) + start, len));
	printf("quote_str%s\n", quote_str);
	//Protection
	data->argc += 1;
	lst_new_back(&data->arg_lst, quote_str);
	printf("%s\n", quote_str);
	(*trimmed) += (len + start);
	printf("%s\n", *trimmed);
}

void	add_arg_string_join(t_data *data, char **trimmed, int *start, char quote)
{
	// save the string from the start of trimmed to i on stack,
	// save inside of the quotes, if a DOUBLE Quote, save inside of quotes and
	// check for valid ENV check, if Single Quote just save letter for letter
	// inside.
	char	*str;
	char	*quote_str;
	int		q_count;
	int		len;

	q_count = 1;
	len = 0;
	while (q_count < 2 && (*trimmed)[*start + 1 + len])
	{
		if ((*trimmed)[*start + 1 + len] == quote)
			q_count += 1;
		len++;
	}
	if (q_count != 2)
		put_error("Your Quotes are shit mate.");
	quote_str = ft_strldup((*trimmed) + *start + 1, len - 1);
	if (quote == D_QOTE)
		quote_str = str_env_replace(data, quote_str, 1);
	printf("quote_str%s\n", quote_str);
	str = ft_strjoin(ft_strldup((*trimmed), *start), quote_str);
	*start = *start + 1 + len;
	len = 0;
	while ((*trimmed)[*start + len] && !iscset((*trimmed)[*start + len], "><|; '\""))
		len++;
	str = ft_strjoin(str, ft_strldup((*trimmed) + *start, len));
	//Protection
	data->argc += 1;
	lst_new_back(&data->arg_lst, str);
	printf("%s\n", str);
	(*trimmed) += (*start + len);
	printf("%s\n", *trimmed);
	*start = 0;
}

void	parse_args(t_data *data, char *trimmed)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	trimmed = trim_spaces(trimmed);
	ft_printf_fd(2, "remaining string_%s\n", trimmed);
	// TODO While not at the end of the string or reading a Quote or Pipe increment end
	// continue to do this until the string is done, if you find the end of the input
	// or you find a QUOTE or PIPE save all input in string at that point, and then handle the
	// case then, incrementing the pointer after
	while (trimmed[i])
	{
		tmp = "";
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE || iscset(trimmed[i], "><|; "))
		{
			if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
			{
				perror("quote");
				if (i > 0)
					add_arg_string_join(data, &trimmed, &i, trimmed[i]);
				else
				{
					add_string(data, &trimmed, trimmed[i]);
					/* trimmed = ft_save_string(data, (trimmed + i + 1), 0, trimmed[i], */
					/* 		trimmed); */
					i = 0;
				}
			}
			else if (trimmed[i] == '>' && trimmed[i + 1] == '>')
			{
				perror("append");
				if (i > 0)
					add_arg(data, &trimmed, &i);
				tmp = ft_strldup(trimmed, 3);
				if (!tmp)
					put_error("Error in arg Parsing");
				if (*tmp)
				{
					data->argc += 1;
					lst_new_back(&data->arg_lst, tmp);
					trimmed += 2;
					i = 0;
				}
			}
			else if (iscset(trimmed[i], ">|;<"))
			{
				perror("redir/semi");
				if (i > 0)
					add_arg(data, &trimmed, &i);
				tmp = ft_strldup(trimmed, 1);
				if (!tmp)
					put_error("Error in Arg Parsing");
				if (*tmp)
				{
					data->argc += 1;
					lst_new_back(&data->arg_lst, tmp);
				}
				trimmed += 1;
				i = 0;
			}
			else if (trimmed[i] == ' ')
			{
				perror("normal arg");
				perror("there");
				if (i > 0)
					add_arg(data, &trimmed, &i);
				while (trimmed[i] == ' ')
					i++;
				trimmed += i;
				i = 0;
			}
		}
		else
			i++;
	}
	if (i > 0)
		add_arg(data, &trimmed, &i);
	// }
	// if (*trimmed == D_QOTE || *trimmed == S_QOTE)
	// 	trimmed = ft_save_string(data, (trimmed + 1), 0, *trimmed, trimmed);
	// else if (*trimmed == '|' || *trimmed == ';' || *trimmed == '<' || *trimmed == '>')
	// 	trimmed = ft_save_flags(data, trimmed, *trimmed);
	// else
	// {
	// 	str = ft_strldup(trimmed, ft_strchr_lib(trimmed, ' ') - trimmed);
	// 	if (!str)
	// 		put_error("Error in argument parsing");
	// 	if (*str)
	// 	{
	// 		if (*str == '<' || *str == '>')
	// 		{
	// 			data->redir_count += 1;
	// 			dprintf(2, "Redir Count = %d\n", data->redir_count);
	// 		}
	// 		data->argc += 1;
	// 		lst_new_back(&data->arg_lst, str);
	// 	}
	// 	trimmed = trimmed + ft_strlen_lib(str);
	// }
	// if (*trimmed)
	// 	parse_args(data, trimmed);
}
