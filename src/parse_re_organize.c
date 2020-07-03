/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/07/02 22:51:40 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cur_cmd(t_input *inp)
{
	int		i;

	i = 0;
	printf("-- PRINT CUR CMD STRUCT --\n");
	if (inp->comd->builtin)
		printf("Builtin_%s\n", inp->comd->builtin);
	if (inp->comd->pipe)
		printf("Pipe_%s\n", inp->comd->pipe);
	if (inp->comd->tar_file)
		printf("Tar File_%s\n", inp->comd->tar_file);
	if (inp->comd->argc)
		printf("Argc_%d\n", inp->comd->argc);
	if (inp->comd->argv)
	{
		while (i < inp->comd->argc)
		{
			printf("ARGV_%s\n",inp->comd->argv[i]);
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
// TODO How to deal with dynamically allocation memory for the 2d array
// TODO is it possible to do it without the linked list?
t_comd		*re_organize(t_input *inp, t_comd *comd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("Argc = %d\nArgv[i]_%s\n", inp->argc, inp->argv[i]);
	while (i < inp->argc)
	{
		if (is_cmd(inp->argv[i]))
		{
			perror("seg 1");
			comd->builtin = ft_strdup(inp->argv[i]);
			perror("seg 2");
			inp->argc -= 1;
			drop_string(inp, i);
		}
		else if (inp->argv[i][0] == '|' || inp->argv[i][0] == ';')
		{
			comd->pipe = ft_strdup(inp->argv[i]);
			inp->argc -= 1;
			drop_string(inp, i);
			comd->argv = split_arg_lst(comd->arr_list); 
			comd = inp->comd->next;
			j = 0;
		}
		else if (inp->argv[i][0] == '<' || inp->argv[i][0] == '>')
		{
			if (!inp->argv[i + 1])
				put_error("could not find newline");
			comd->pipe = ft_strdup(inp->argv[i]);
			inp->argc -= 1;
			comd->tar_file = ft_strdup(inp->argv[i + 1]);
			drop_string(inp, i);
			drop_string(inp, i + 1);
			comd->argv = split_arg_lst(comd->arr_list); 
			comd = comd->next;
			j = 0;
			i += 1;
		}
		else
		{
			lst_new_back(&comd->arr_list, inp->argv[i]);
			/* inp->comd->argv[j] = ft_strdup(inp->argv[i]); */
			comd->argc += 1;
			inp->argc -= 1;
			drop_string(inp, i);
		}
		i++;
	}
	if (comd->arr_list && !comd->pipe)
		comd->argv = split_arg_lst(comd->arr_list);
	return (comd);

}

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
*/

void	parse_organize(t_input *inp)
{
	t_comd	*comd;

	comd = inp->comd;
	inp->comd = re_organize(inp, comd);
	// count through for a pipe store if found check argv for a builtin
	// save the builtin, and the rest of the argv UNTIL the pipe to the struct
	// if REDIR save NEXT argv to tar_file, imp->cmd->next
}
