/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fd_sto_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/30 11:15:20 by averheij      #+#    #+#                 */
/*   Updated: 2020/10/21 17:27:30 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		sto_fd(t_fd_sto *fd, int add_fd)
{
	int		*temp;

	if (!fd->arr || fd->mem == 0)
	{
		fd->arr = ft_calloc(1, sizeof(int));
		if (!fd->arr)
			return (1);
		fd->mem = 1;
		fd->used = 0;
	}
	else if (fd->mem == fd->used)
	{
		temp = ft_calloc(fd->mem * 2, sizeof(int));
		if (!temp)
			return (1);
		temp = ft_memcpy(temp, fd->arr, fd->used * sizeof(int));
		ft_free((void **)&fd->arr);
		fd->arr = temp;
		fd->mem *= 2;
	}
	fd->arr[fd->used] = add_fd;
	fd->used++;
	return (0);
}

void	close_fd(t_fd_sto *fd, int io_fd[2])
{
	int		i;
	int		cur;

	i = 0;
	while (i < fd->used)
	{
		cur = fd->arr[i];
		if (io_fd && cur != io_fd[0] && cur != io_fd[1])
			close(cur);
		i++;
	}
	ft_free((void **)&fd->arr);
	fd->mem = 0;
	fd->used = 0;
}
