/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:08:02 by greed         #+#    #+#                 */
/*   Updated: 2020/06/21 11:12:52 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** need to trim spaces until first none ' '
** CMD == from first CHAR -> ' '
** after this is saved, the DATA input NEEDS to be trim
** EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR
*/

char	*del_leading_space(char *res)
{
	while (*res)
	{
		if (ft_isalpha(*res) != 1)
			res++;
		else
			break ;
	}
	return (res);
}

/*
** Saves from start of string to the first occurence of a non alpha 
** Null terminating the string
** Prepares trimmed for use in ARG
*/

char	*parse_cmd(t_input *inp, char *trimmed)
{
	int	i;

	i = 0;
	while (ft_isalpha(trimmed[i]))
		i++;
	inp->cmd = ft_strldup(trimmed, i);
	if (!inp->cmd)
		put_error("Invalid Command Given");
	trimmed = trimmed + i;
	return (trimmed);
}