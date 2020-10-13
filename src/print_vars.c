/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vars.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:54 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 14:04:04 by averheij      ########   odam.nl         */
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
		dprintf(2,"env:%p|%s=%s\n", env->val, (char*)env->name, env->val);
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
	print_args(data);
}

void	print_cur_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	dprintf(2,"-- PRINT CUR CMD STRUCT --\n");
	if (cmd->builtin)
		dprintf(2,"Builtin_%s\n", cmd->builtin);
	if (cmd->io_fd[IN] != -1)
		dprintf(2,"Redir In_%d\n", cmd->io_fd[IN]);
	if (cmd->io_fd[OUT] != -1)
		dprintf(2,"Redir Out_%d\n", cmd->io_fd[OUT]);
	if (cmd->pipe_read_end != -1)
		dprintf(2,"Pipe Read_%d\n", cmd->pipe_read_end);
	if (cmd->tar_file)
		dprintf(2,"Tar File_%s\n", cmd->tar_file);
	if (cmd->argc)
		dprintf(2,"Argc_%d\n", cmd->argc);
	if (cmd->argv)
	{
		while (i < cmd->argc)
		{
			dprintf(2,"ARGV[%d]_%s\n", i, cmd->argv[i]);
			i++;
		}
	}
}

void	print_cmd_full(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = data->cmd;
	while (cmd)
	{
		print_cur_cmd(cmd);
		cmd = cmd->next;
	}
}
