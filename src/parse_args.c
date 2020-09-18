/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 15:23:31 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** need to trim spaces until first non ' '
** CMD == from first CHAR -> ' '
** after this is saved, the DATA input NEEDS to be trim
** EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR
*/

/* 
** split arg_lst into argc argv for easier access
*/

int		ft_env_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

/*
** When triggered by a '$', save through to the next '$' || '\0' || ' '
** IF the characters inside != UPPER CASE APHLA dont save shit inside
*/

char	*ft_save_dolla(t_data *data, char *trimmed, int start)
{
	char	*str;
	int		i;
	int		skip;

	skip = 0;
	i = 0;
	while (trimmed[start] != '$' && trimmed[start] != ' ' &&
				trimmed[start] != '\0')
	{
		if (ft_env_char(trimmed[start]) == 0)
			skip = 1;
		i++;
		start++;
	}
	if (skip == 0)
	{
		str = ft_strldup(trimmed, i + 1);
		if (!str)
			put_error("Error in arguement parsing");
		printf("STR $ check =_%s_\n", str);
		if (*str)
		{
			data->argc += 1;
			lst_new_back(&data->arg_lst, str);
		}
	}
	trimmed = trimmed + i + 1;
	return (trimmed);
}

/*
** check the pipe TYPE and save it, if REDIR type, save target file and
** move pointer forward ALSO MOVE INTO CMD->NEXT
*/

/*
** check starting pos, see what the char is there Quote or Dquote
** save from +1 of start until next occurence of Quote
*/

/*
** save until non alpha into args[i]
** IF read a Quote or Dquote send to save with quotes
** trim_spaces after each arg is saved
** maybe can do this recursively
** save everything from SP to SP, SP is 32 in ascii dec
** EASIER WAY, save each arg into linked list, split into array
** after it's fully finished
*/

void	parse_args(t_data *data, char *trimmed)
{
	char	*str;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	trimmed = trim_spaces(trimmed);
	ft_printf_fd(2, "remaining string_%s\n", trimmed);
	/* not cucked above this /\/\/\/\/\/\ */
	while (trimmed && trimmed[i] != ' ' && trimmed[i] != '\0')
	{
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
		{
			trimmed = ft_save_literal(data, (trimmed + 1), i, trimmed[i], trimmed);
			if (!*trimmed)
			{
				printf("I guess this shit is NULL\n");
				return ;
			}
			printf("trimmed after SAVE QUOTE_%s_\n", trimmed);
		}
		else if (trimmed[i] == '$')
			trimmed = ft_save_dolla(data, trimmed, (i + 1));
		else
			i++;
	}
	str = ft_strldup(trimmed, i);
	if (!str)
		put_error("Error in argument parsing");
	if (*str)
	{
		data->argc += 1;
		lst_new_back(&data->arg_lst, str);
	}
	trimmed = trimmed + i;
	if (*trimmed)
		parse_args(data, trimmed);
}
