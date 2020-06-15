/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:46:17 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 14:17:33 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*link;
	t_list		*next_link;

	if (!(lst))
		return ;
	link = *lst;
	while (link)
	{
		next_link = link->next;
		del(link->content);
		free(link);
		link = next_link;
	}
	*lst = NULL;
}
