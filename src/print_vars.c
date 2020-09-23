/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vars.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:54 by greed         #+#    #+#                 */
/*   Updated: 2020/09/23 13:40:06 by averheij      ########   odam.nl         */
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
		dprintf(2,"ENV_TEST_%s\n", environ[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	while (list)
	{
		dprintf(2,"lst:%p|%s\n", list->content, (char*)list->content);
		list = list->next;
	}
}

void	print_env(t_var *env)
{
	while (env)
	{
		dprintf(2,"env:%p|%s=%s\n", env, (char*)env->name, env->val);
		env = env->next;
	}
}

void	print_args(t_data *data)
{
	int	y;

	y = 0;
	dprintf(2,"--------\nPRINTING ARGS\nARGC = %d\n", data->argc);
	while (y < data->argc)
	{
		dprintf(2,"\t%s\n", data->argv[y]);
		y++;
	}
}

void	test_args(char **argv, int argc)
{
	int	y;

	y = 0;
	dprintf(2,"*** TESTING FT EXEC ARGS ***\n");
	while (argv[y])
	{
		dprintf(2,"\t_%s\n", argv[y]);
		y++;
	}
}

void	print_vars(t_data *data)
{
	/* ft_printf("CMD = %s\n", data->cmd); */
	print_args(data);
}
