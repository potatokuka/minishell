/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 16:20:14 by greed         #+#    #+#                 */
/*   Updated: 2020/06/19 14:00:17 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!(lst))
		return (0);
	res = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!(new))
			ft_lstclear(&lst, del);
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
