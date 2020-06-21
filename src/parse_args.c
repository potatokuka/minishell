/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/06/21 11:10:33 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** need to trim spaces until first none ' '
** CMD == from first CHAR -> ' '
** after this is saved, the DATA input NEEDS to be trim
** EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR
*/

char	*del_lead_arg(char *res)
{
	while (*res)
	{
		if (*res == ' ')
			res++;
		else
			break ;
	}
	return (res);
}

/* 
** split arg_lst into argc argv for easier access
*/

void	split_arg_lst(t_input *inp)
{
	char	**tmp;
	char	*str;
	t_list	*lst;
	int		size_len;
	int		x;

	x = 0;
	size_len = lst_size(inp->arg_lst);
	inp->argc = size_len;
	tmp = (char **)malloc(sizeof(char *) * size_len);
	lst = inp->arg_lst;
	while (x < size_len)
	{
		str = lst->content;
		tmp[x] = ft_strdup_lib(str);
		lst = lst->next;
		x++;
	}
	inp->argv = tmp;
}

/*
** When triggered by a '$', save through to the next '$' || '\0' || ' '
** IF the characters inside != UPPER CASE APHLA dont save shit inside
*/

/*
** check starting pos, see what the char is there Quote or Dquote
** save from +1 of start until next occurence of Quote
*/

char	*ft_save_quote(t_input *inp, char *trimmed, int start, char quote)
{
	char	*str;
	int	i;

	i = 0;
	while (trimmed[start] != quote && trimmed[start])
	{
		i++;
		start++;
	}
	str = ft_strldup(trimmed, i);
	if (*str)
		lst_new_back(&inp->arg_lst, str);
	trimmed = trimmed + (i + 1);
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
	trimmed = del_lead_arg(trimmed);
	while (trimmed[i] != ' ' && trimmed[i] != '\0')
	{
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
			trimmed = ft_save_quote(inp, (trimmed + 1), i, trimmed[i]);
		else
			i++;
	}
	str = ft_strldup(trimmed, i);
	if (*str)
	{
		lst_new_back(&inp->arg_lst, str);
	}
	run_time++;
	if (trimmed[i + 1])
	{
		trimmed = trimmed + i;
		parse_args(inp, trimmed, run_time);
		return ;
	}
}
