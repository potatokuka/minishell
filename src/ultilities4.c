/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities4.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/19 13:28:27 by averheij      #+#    #+#                 */
/*   Updated: 2020/11/05 15:27:31 by averheij      ########   odam.nl         */
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

void		*reset_prompt_cmd(t_data *data, t_cmd *cmd, char *fterror,
								int error_val)
{
	free_cmd(cmd);
	reset_prompt(data, fterror, error_val, 0);
	return (NULL);
}

void		*free_ret_null(char *free_me, char *me_too)
{
	if (me_too)
		free(me_too);
	if (free_me)
		free(free_me);
	return (NULL);
}
