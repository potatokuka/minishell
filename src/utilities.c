/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:49 by greed         #+#    #+#                 */
/*   Updated: 2020/06/19 18:05:50 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_strlcpy(combined, str1, ft_strlen(str1) + 1);
	ft_strlcpy(combined + ft_strlen(str1), str2, ft_strlen(str2) + 1);
	ft_strlcpy(combined + ft_strlen(str1) +ft_strlen(str2), str3,
			ft_strlen(str3) + 1);
	return(combined);
}
void	reset_input(t_input *inp)
{
	if (inp->argv)
		fre_array(inp->argv);
	return ;
}

void	error_builtin(t_input *inp)
{
	int	i;

	i = 0;
	ft_printf_fd(2, "%s", inp->argv[i]);
	ft_printf_fd(2, "%s: ", strerror(errno));
	i += 1;
	while (inp->argc > 1)
	{
		if (inp->argc > 1)
		{
			printf(" ");
			i += 1;
			inp->argc -= 1;
		}
		else
		{
			printf("\n");
			return ;
		}
	}
	printf("\n");
}
