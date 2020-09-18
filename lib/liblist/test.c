/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abe <marvin@42.fr>                           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 09:41:44 by abe           #+#    #+#                 */
/*   Updated: 2020/09/18 18:11:21 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/*
**	Some tests to test the general functionality of the list functions.
*/

void	test_lst_new()
{
	t_list	*node;
	char	*content;

	content = (char *)malloc(5);
	strcpy(content, "test");
	node = lst_new(content);
	assert(node->next == NULL);
	assert(node->prev == NULL);
	assert(node->content == content);
	assert(strcmp((char *)node->content, "test") == 0);
	free(content);
	free(node);
}

void	test_lst_new_back()
{
	t_list	*node;
	t_list	*res;
	char	*content;
	char	*content2;

	content = (char *)malloc(5);
	strcpy(content, "test");
	node = lst_new_back(NULL, content);
	assert(node->next == NULL);
	assert(node->prev == NULL);
	assert(node->content == content);
	assert(strcmp((char *)node->content, "test") == 0);

	content2 = (char *)malloc(5);
	strcpy(content2, "tes2");
	res = lst_new_back(node, content2);
	assert(res == node->next);
	assert(res->prev == node);
	assert(res->content == content2);
	assert(strcmp((char *)res->content, "tes2") == 0);
	free(node);
	free(res);
	free(content);
	free(content2);
}

void	test_lst_new_front()
{
	t_list	*node, *cpy;
	char	*content, *content2;
	
	content = malloc(5);
	strcpy(content, "test");
	node = lst_new(content);
	cpy = node;
	content2 = malloc(5);
	strcpy(content2, "tes2");
	lst_new_front(&node, content2);
	assert(node->prev == NULL);
	assert(node->next == cpy);
	assert(node->content == content2);
	assert(cpy->prev == node);
	assert(cpy->next == NULL);
	assert(cpy->content == content);
	free(content);
	free(content2);
	free(node);
	free(cpy);
}

void	free_func(void *content)
{
	free(content);
}

void	test_lst_remove()
{
	t_list	*node;
	char	*content1, *content2, *content3;

	content1 = strdup("test1");
	content2 = strdup("test2");
	content3 = strdup("test3");
	node = lst_new(content1);
	lst_new_back(node, content2);
	lst_new_back(node, content3);
	lst_remove(node->next, &free_func);
	assert(node->next->content == content3);
	assert(node->next->prev == node);
	free(content1);
	free(content3);
	free(node->next);
	free(node);
}

void	test_lst_reverse()
{
	t_list	*node;
	char	*content1, *content2, *content3;

	content1 = strdup("test1");
	content2 = strdup("test2");
	content3 = strdup("test3");
	node = lst_new(content1);
	lst_new_back(node, content2);
	lst_new_back(node, content3);
	lst_reverse(&node);
	assert(node->content == content3);
	assert(node->next->content == content2);
	assert(node->next->next->content == content1);
	assert(node->next->next->next == NULL);
	assert(node->next->prev == node);
	assert(node->next->next->prev == node->next);
	free(node->next->next);
	free(node->next);
	free(node);
	free(content1);
	free(content2);
	free(content3);
}

void	test_lst_size()
{
	t_list	*node;

	node = lst_new(NULL);
	lst_new_back(node, NULL);
	lst_new_back(node, NULL);
	assert(lst_size(node) == 3);
	lst_remove(node->next, &free_func);
	assert(lst_size(node) == 2);
	lst_remove(node->next, &free_func);
	assert(lst_size(node) == 1);
	free(node);
	assert(lst_size(NULL) == 0);
}

void	func(void *content)
{
	char *str = (char *)content;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str = *str - 'a' + 'A';
		str++;
	}
}

void	test_lst_foreach()
{
	t_list	*node;
	char	*content1, *content2, *content3;

	content1 = strdup("test1");
	content2 = strdup("test2");
	content3 = strdup("test3");
	node = lst_new(content1);
	lst_new_back(node, content2);
	lst_new_back(node, content3);
	lst_foreach(node, &func);
	assert(strcmp(node->content, "TEST1") == 0);
	assert(strcmp(node->next->content, "TEST2") == 0);
	assert(strcmp(node->next->next->content, "TEST3") == 0);
	free(content1);
	free(content2);
	free(content3);
	free(node->next->next);
	free(node->next);
	free(node);
}

int		main(void)
{
	test_lst_new();
	test_lst_new_back();
	test_lst_new_front();
	test_lst_remove();
	test_lst_reverse();
	test_lst_size();
	test_lst_foreach();
	dprintf(2,"Everything is fine!\n");
}
