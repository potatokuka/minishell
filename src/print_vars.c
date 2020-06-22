/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vars.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:54 by greed         #+#    #+#                 */
/*   Updated: 2020/06/22 23:10:55 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_environ(char **environ)
{
	int		height;
	int		i;

	height = 0;
	i = 0;
	while (environ[height])
		height++;
	while (i < height)
	{
		printf("ENV_TEST_%s\n", environ[i]);
		i++;	
	}
}

void	print_list(t_list *list)
{
	while (list)
	{
		printf("lst:%p|%s\n", list->content, (char*)list->content);
		list = list->next;
	}
}

void	print_args(t_input *inp)
{
	int	y;

	y = 0;
	printf("--------\nPRINTING ARGS\nARGC = %d\n", inp->argc);
	while (y < inp->argc)
	{
		printf("%s\n", inp->argv[y]);
		y++;
	}
}

void	print_vars(t_input *inp)
{
	ft_printf("CMD = %s\n", inp->cmd);
	print_args(inp);
}
