/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:08:02 by greed         #+#    #+#                 */
/*   Updated: 2020/06/25 14:34:00 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** need to trim spaces until first none ' '
** CMD == from first CHAR -> ' '
** after this is saved, the DATA input NEEDS to be trim
** EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR
*/

char	*trim_spaces(char *res)
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
** Returns 1 if the given string matches to a builtin
*/

int		is_builtin(char *cmd)
{
	int	len;

	len = (ft_strlen_lib(cmd) + 1);
	if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", len) == 0)
	{
		perror("inside this shit");
		return (1);
	}
	else if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	else
		return (0);
}

/*
** Saves from start of string to the first occurence of a non alpha 
** Null terminating the string
** Prepares trimmed for use in ARG
*/

