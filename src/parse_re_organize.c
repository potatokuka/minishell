/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/07/03 17:32:31 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print_arr(char **argv, int argc)
{
	int i;

	i = 0;
	printf("-- * TEST PRINT ARR * --\n");
	while (i < argc)
	{
		printf("argv[%d]_%s\n", i, argv[i]);
		i++;
	}
}
void	print_comd_full(t_input *inp)
{
	t_comd	*comd;
	int		i;

	i = 0;
	comd = inp->comd;
	while (comd)
	{
		printf("-- PRINT CUR CMD STRUCT --\n");
		if (comd->builtin)
			printf("Builtin_%s\n",comd->builtin);
		if (comd->pipe)
			printf("Pipe_%s\n",comd->pipe);
		if (comd->tar_file)
			printf("Tar File_%s\n",comd->tar_file);
		if (comd->argc)
			printf("Argc_%d\n",comd->argc);
		if (comd->argv)
		{
			while (i < comd->argc)
			{
				printf("ARGV_%s\n",comd->argv[i]);
				i++;
			}
		}
		comd = comd->next;
	}
}

void	print_cur_cmd(t_comd *comd)
{
	int		i;

	i = 0;
	printf("-- PRINT CUR CMD STRUCT --\n");
	if (comd->builtin)
		printf("Builtin_%s\n", comd->builtin);
	if (comd->pipe)
		printf("Pipe_%s\n", comd->pipe);
	if (comd->tar_file)
		printf("Tar File_%s\n", comd->tar_file);
	if (comd->argc)
		printf("Argc_%d\n", comd->argc);
	if (comd->argv)
	{
		while (i < comd->argc)
		{
			printf("ARGV[%d]_%s\n", i, comd->argv[i]);
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

int				clear_comd(t_comd *comd, void(*del)(void *))
{
	t_comd	*delete;

	while (comd)
	{
		delete = comd;
		comd = comd->next;
		if (delete->builtin)
			del(delete->builtin);
		if (delete->pipe)
			del(delete->pipe);
		if (delete->tar_file)
			del(delete->tar_file);
		if (delete->argv)
		{
			fre_array(delete->argv);
			del(delete->argv);
		}
	}
	return (0);
}

static t_comd	*split_init(t_input *inp)
{
	t_comd	*new;
	int		i;

	new = ft_calloc(sizeof(t_comd), 1);
	i = 0;
	if (!new)
		return (NULL);
	// TODO run the orgainze until it finds delimiter
	printf("SPLIT INIT FIRST ORGC %d\n", inp->org_argc);
	while (inp->org_argc < inp->argc)
	{
		if (is_cmd(inp->argv[i]))
		{
			new->builtin = ft_strdup(inp->argv[i]);
			drop_string(inp, i);
			inp->argc -= 1;
		}
		else if (inp->argv[i][0] == '|' || inp->argv[i][0] == ';')
		{
			new->pipe = ft_strdup(inp->argv[i]);
			drop_string(inp, i);
			printf("Else if pipe\n");
			print_list(new->arr_list);
			new->argv = split_arg_lst(new->arr_list);
			test_print_arr(new->argv, new->argc);
			inp->argc -= 1;
			new->next = NULL;
			return (new);
		}
		else if (inp->argv[i][0] == '<' || inp->argv[i][0] == '>')
		{
			if (!inp->argv[i + 1])
				put_error("could not find newline");
			new->pipe = ft_strdup(inp->argv[i]);
			new->tar_file = ft_strdup(inp->argv[i + 1]);
			drop_string(inp, i);
			i += 1;
			drop_string(inp, i);
			inp->argc -= 2;
			new->argv = split_arg_lst(new->arr_list);
			new->next = NULL;
			return (new);
		}
		else
		{
			printf("adding to back %d_%s\n", i, inp->argv[i]);
			lst_new_back(&new->arr_list, ft_strdup(inp->argv[i]));
			print_list(new->arr_list);
			/* inp->comd->argv[j] = ft_strdup(inp->argv[i]); */
			new->argc += 1;
			inp->org_argc += 1;
			drop_string(inp, i);
		}
		i++;
	}
	/* inp->org_argc += i; */
	if (new->arr_list && !new->pipe)
		new->argv = split_arg_lst(new->arr_list);
	new->next = NULL;
	return (new);
}

static int	comd_head_init(t_input *inp, char **argv)
{
	inp->comd = NULL;
	if (!argv || !argv[0])
		return (-1);
	inp->comd = split_init(inp);
	if (!inp->comd)
		return (clear_comd(inp->comd, &free));
	return (-1);
}

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
*/

int	parse_organize(t_input *inp)
{
	t_comd	*comd;
	int		i;
	int		n;

	i = comd_head_init(inp, inp->argv);
	printf("OUT OF HEAD INIT\n");
	n = 0;
	if (i != -1)
		return (i);
	i = 1;
	printf("This moves, comd to imp->comd\n");
	comd = inp->comd;
	print_cur_cmd(comd);
	printf(" *** org argc %d inp argc %d\n", inp->org_argc, inp->argc);
	while (inp->org_argc < inp->argc)
	{
		printf("counter %d\n", n);
		n++;
		comd->next = split_init(inp);
		if (!comd->next)
			return (clear_comd(inp->comd, &free));
		perror("1");
		comd = comd->next;
		print_cur_cmd(comd);
		inp->org_argc += 1;
	}
	inp->comd = comd;
	print_comd_full(inp);
	return (0);
	// count through for a pipe store if found check argv for a builtin
	// save the builtin, and the rest of the argv UNTIL the pipe to the struct
	// if REDIR save NEXT argv to tar_file, imp->cmd->next
}
