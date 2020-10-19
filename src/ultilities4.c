/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities4.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 13:28:27 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/19 13:28:42 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*safestrjn(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
