/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/07/14 14:31:26 by averheij      ########   odam.nl         */
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

char	**split_arg_lst(t_list *to_copy)
{
	char	**tmp;
	char	*str;
	t_list	*lst;
	int		size_len;
	int		x;

	x = 0;
	size_len = lst_size(to_copy);
	/* inp->argc = size_len; */
	tmp = (char **)ft_calloc(sizeof(char *), size_len + 1);
	lst = to_copy;
	while (x < size_len)
	{
		/*tmp[x] = lst->content;*/ //TODO why not just give lst->content address to tmp[i], and set lst->content to null, then dont need str, tried just now but I got errors and im too lazy to see why
		str = lst->content;
		tmp[x] = ft_strdup_lib(str);
		lst = lst->next;
		x++;
	}
	return (tmp);
}

int		ft_env_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

/*
** When triggered by a '$', save through to the next '$' || '\0' || ' '
** IF the characters inside != UPPER CASE APHLA dont save shit inside
*/

char	*ft_save_dolla(t_input *inp, char *trimmed, int start)
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
			inp->argc += 1;
			lst_new_back(&inp->arg_lst, str);
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

char	*ft_save_quote(t_input *inp, char *trimmed, int start, char quote)
{
	char	*str;
	int		i;

	i = 0;
	while (trimmed[start] != quote && trimmed[start])
	{
		i++;
		start++;
	}
	str = ft_strldup(trimmed, i);
	if (!str)
		put_error("Error in arguement parsing");
	if (*str)
	{
		inp->argc += 1;
		lst_new_back(&inp->arg_lst, str);
	}
	trimmed = trimmed + i;
	return (trimmed);
}

/*
** save until non alpha into args[i]
** IF read a Quote or Dquote send to save with quotes
** del_leading_space after each arg is saved
** maybe can do this recursively
** save everything from SP to SP, SP is 32 in ascii dec
** EASIER WAY, save each arg into linked list, split into array
** after it's fully finished
*/

void	parse_args(t_input *inp, char *trimmed, int run_time)
{
	char	*str;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	trimmed = del_leading_space(trimmed);
	while (trimmed[i] != ' ' && trimmed[i] != '\0')
	{
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
			trimmed = ft_save_quote(inp, (trimmed + 1), i, trimmed[i]);
		else if (trimmed[i] == '$')
			trimmed = ft_save_dolla(inp, trimmed, (i + 1));
		/*else if (trimmed[i] == '>' || trimmed[i] == '>' || trimmed[i] == ';'*/
				/*|| trimmed[i] == '|')*/
			/*trimmed = ft_save_pipe(inp, trimmed, i);*/
		else
			i++;
	}
	str = ft_strldup(trimmed, i);
	if (!str)
		put_error("Error in arguement parsing");
	if (*str)
	{
		inp->argc += 1;
		lst_new_back(&inp->arg_lst, str);
	}
	trimmed = trimmed + i;
	if (*trimmed)
		parse_args(inp, trimmed, run_time);
}
