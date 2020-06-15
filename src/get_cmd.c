/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 18:10:22 by greed         #+#    #+#                 */
/*   Updated: 2020/06/15 18:10:30 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_shell *shell)
{
  char	*res;
  
  res = NULL;
  if (shell->init == 0)
    if (get_next_line(STDIN, &res) < 0)
      put_error("Error on CMD input");
  return (res);
}
