/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_to_char_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 19:43:57 by greed         #+#    #+#                 */
/*   Updated: 2020/10/05 14:00:54 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_string_array(t_list *to_copy)
{
	char	**tmp;
	char	*str;
	t_list	*lst;
	int		size_len;
	int		x;

	x = 0;
	size_len = lst_size(to_copy);
	tmp = (char **)ft_calloc(sizeof(char *), size_len + 1);
	if (!tmp)
		return (NULL);
	lst = to_copy;
	while (x < size_len)
	{
		/*tmp[x] = lst->content;*/ //TODO why not just give lst->content address to tmp[i], and set lst->content to null, then dont need str, tried just now but I got errors and im too lazy to see why
		str = lst->content;
		tmp[x] = ft_strdup_lib(str);//Leaks
		lst = lst->next;
		x++;
	}
	return (tmp);
}
