/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:49 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 14:16:19 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** count the len unti it reaches the sent char
*/

int		ft_is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else
		return (0);
}
size_t	ft_strc_len(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*ft_combine_str(const char *str1, const char *str2,
			const char *str3)
{
	char	*combined;

	if (!str1 || !str2 || !str3)
		return (NULL);
	combined = (char *)ft_calloc(ft_strlen_lib(str1) + ft_strlen_lib(str2)
			+ ft_strlen_lib(str3) + 1, sizeof(char));
	if (!combined)
		return (NULL);
	ft_strlcpy_lib(combined, str1, ft_strlen_lib(str1) + 1);
	ft_strlcpy_lib(combined + ft_strlen_lib(str1), str2,
			ft_strlen_lib(str2) + 1);
	ft_strlcpy_lib(combined + ft_strlen_lib(str1) + ft_strlen_lib(str2),
			str3, ft_strlen_lib(str3) + 1);
	return(combined);
}
void	reset_input(t_input *inp)
{
	if (inp->argv)
		inp->argv = (void *)0;
		/*free_array_null(inp->argv);*/
	inp->argc = 0;
	/*if (inp->redirs)*/
		/*free_array_null(inp->redirs);*/
	inp->arg_lst = (void *)0;
	inp->cmd = (void *)0;
	return ;
}

void	error_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_printf_fd(2, "%s", cmd->argv[i]);
	ft_printf_fd(2, "%s: ", strerror(errno));
	i += 1;
	while (cmd->argc > 1)
	{
		if (cmd->argc > 1)
		{
			printf(" ");
			i += 1;
			cmd->argc -= 1;
		}
		else
		{
			printf("\n");
			return ;
		}
	}
	printf("\n");
}
