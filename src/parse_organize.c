/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_organize.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/07/02 16:56:48 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cur_cmd(t_input *inp)
{
	int		i;

	i = 0;
	printf("-- PRINT CUR CMD STRUCT --\n");
	if (inp->cmd->builtin)
		printf("Builtin_%s\n", inp->cmd->builtin);
	if (inp->cmd->pipe)
		printf("Pipe_%s\n", inp->cmd->pipe);
	if (inp->cmd->tar_file)
		printf("Tar File_%s\n", inp->cmd->tar_file);
	if (inp->cmd->argc)
		printf("Argc_%d\n", inp->cmd->argc);
	if (inp->cmd->argv)
	{
		while (i < argc)
		{
			printf("ARGV_%s\n",inp->cmd->argv[i]);
			i++;
		}
	}
}

int		drop_string(t_input *inp, int i)
{
	if (inp->argv[i])
		free(inp->argv[i]);
	inp->argv[i] = NULL;
	return (0);
}

/* JUST FUCKING PARSE UNtIL A DELEMETER JUST FUCKING DONT BE A BITCH */
void	re_organize(t_input *inp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < inp->argc)
	{
		if (is_cmd(inp->argv[i]))
		{
			inp->cmd->builtin = ft_strdup(inp->argv[i]);
			inp->argc -= 1;
			drop_string(inp, i);
		}
		else if (inp->argv[i][0] == '|' || inp->argv[i][0] == ';')
		{
			inp->cmd->pipe = ft_strdup(inp->argv[i]);
			inp->argc -= 1;
			drop_string(inp, i);
			inp->cmd = inp->cmd->next;
			j = 0;
		}
		else if (inp->argv[i][0] == '<' || inp->argv[i][0] == '>')
		{
			if (!inp->argv[i + 1])
				put_error("could not find newline");
			inp->cmd->pipe = ft_strdup(inp->argv[i]);
			inp->argc -= 1;
			inp->cmd->tar_file = ft_strdup(inp->argv[i + 1]);
			drop_string(inp, i);
			drop_string(inp, i + 1);
			inp->cmd = inp->cmd->next;
			j = 0;
			i += 1;
		}
		else
		{
			inp->cmd->argv[j] = ft_strdup(inp->argv[i]);
			inp->cmd->argc += 1;
			inp->argc -= 1;
			drop_string(inp, i);
		}
		i++;
	}
}

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
*/

void	parse_organize(t_input *inp)
{
	re_organize(t_input);
	// count through for a pipe store if found check argv for a builtin
	// save the builtin, and the rest of the argv UNTIL the pipe to the struct
	// if REDIR save NEXT argv to tar_file, imp->cmd->next
}
