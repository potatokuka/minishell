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

void	ft_save_redir(t_input *inp, int count)
{
	int		i;
	int		j;

	i = 0;
	j = count;
	inp->cmd->argv = (char **)ft_calloc(sizeof(char *), count);
	while (i < count)
	{
		if (is_cmd(inp->argv[i]))
			inp->cmd->builtin = ft_strdup(inp->argv[i])
		else if (inp->argv[i][0] == '>' || inp->argv[i][0] == '<')
		{
			if (!inp->argv[i + 1])
				put_error("no newline found save redir");
			inp->cmd->pipe = ft_strdup(inp->argv[i]);
			inp->cmd->tar_file = ft_strdup(inp->argv[i + 1]);
			break ;
		}
		else
			inp->cmd->argv[i] = ft_strdup(inp->argv[i]);
		i++;
	}
	inp->cmd = inp->cmd->next;
}

void	ft_organize_inp(t_input *inp)
{
	int		count;
	int		j;

	count = 0;
	j = 0;
	while (count < inp->pipe_count)
	{
		if (inp->argv[i][0] == ';' || inp->argv[i][0] == '|' || inp->argv[i][0] == '>'
				|| inp->argv[i][0] == '<')
		{
			if (inp->argv[i][0] == '>' || inp->argv[i][0] == '<')
				ft_save_redir(inp, i);
			inp->pipe_count -= 1;
			i++;
		}
		else
			i++;
	}

}

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
*/

void	parse_organize(t_input *inp)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	// count through for a pipe store if found check argv for a builtin
	// save the builtin, and the rest of the argv UNTIL the pipe to the struct
	// if REDIR save NEXT argv to tar_file, imp->cmd->next
	while (i < inp->argc)
	{
		if (inp->argv[i][0] == ';' || inp->argv[i][0] == '|' || inp->argv[i][0] == '>'
				|| inp->argv[i][0] == '<')
		{
			inp->pipe_count += 1;
			i++;
		}
		else
			i++;
	}
	ft_organize_inp(inp);
}
