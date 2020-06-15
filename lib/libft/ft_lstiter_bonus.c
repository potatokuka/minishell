/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 16:07:17 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 14:17:33 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!(lst))
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
