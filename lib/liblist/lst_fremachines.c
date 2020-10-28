/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lst_fremachines.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 14:05:20 by greed         #+#    #+#                 */
/*   Updated: 2020/10/28 14:05:21 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"
#include <stdlib.h>

void			fre_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void			fremashin(char **words, int j)
{
	while (j != 0)
	{
		j--;
		if (words[j])
			free(words[j]);
	}
	free(words);
}

void			free_list(t_list *list, void (*func)(void *))
{
	t_list		*tmp;

	while (list)
	{
		tmp = list->next;
		func(list->content);
		free(list);
		list = tmp;
	}
}

void			free_this(char **array)
{
	int y;

	y = 0;
	while (array[y])
	{
		free(array[y]);
		y++;
	}
	free(array);
}
