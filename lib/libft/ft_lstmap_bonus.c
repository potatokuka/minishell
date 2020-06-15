/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 16:20:14 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 15:07:04 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*content;

	if (!(lst))
		return (0);
	res = 0;
	while (lst)
	{
		content = f(lst->content);
		new = ft_lstnew(f(lst->content));
		if (!(new))
			ft_lstclear(&lst, del);
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
