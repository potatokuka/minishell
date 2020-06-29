/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_action.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 13:36:22 by greed         #+#    #+#                 */
/*   Updated: 2020/06/28 13:36:27 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** check if CMD triggered, if it is not then just run the REDIR normal
** if if not run check the cmd, and then put into the directed file
** **** TAKE FROM HERE >> MOVE TO HERE ****
*/

/*
** check to see what kind of flag is given, direct to correct function 
*/

void	redir_append(t_input *inp)
{
	int		i;
	int		fd;
	int		ret;

	i = 0;
	printf("inside of REDIR APPEND\n");
	while (inp->argv[i])
	{
		if (ft_strncmp(inp->argv[i], ">>", 2) == 0)
		{
			
			printf("FILE TO SAVE TO = %s\n", inp->argv[i+1]);
			fd = open(inp->argv[i + 1], O_CREAT | O_APPEND | O_WRONLY);
			if (fd < 0)
				put_error("Error with REDIR Append FD");
			ret = dup2(fd, 1);
			if (ret < 0)
				put_error("Error with REDIR Append Dup2");
			return ;
		}
		else
			i++;
	}
}

void	redir_dispatch(t_input *inp)
{
	int		i;

	i = 0;
	printf("INSIDE OF REDIR_DISPATCH\n");
	printf("redirs[%d]= %s\n", i, inp->redirs[i]);
	if (ft_strncmp(inp->redirs[i], ">>", 2) == 0)
		redir_append(inp);
	/* else if (ft_strncmp(inp->redirs[i], "<", 1)) */
	/* 	redir_std_input(inp); */
	/* else if (ft_strncmp(inp->redirs[i], ">", 1)) */
	/* 	redir_std_out(inp); */
	perror("didnt go inside\n");
	return ;
}
