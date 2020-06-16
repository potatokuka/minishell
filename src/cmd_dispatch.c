/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:53 by greed         #+#    #+#                 */
/*   Updated: 2020/06/16 22:10:54 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_dispatch(t_shell *shell)
{
  if (ft_strcmp(shell->cmd, "exit") == 0)
    ft_exit(shell);
  else if (ft_strcmp(shell->cmd, "echo") == 0)
    ft_echo(shell);
  return ;
}
