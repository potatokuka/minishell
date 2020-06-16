/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 18:26:52 by greed         #+#    #+#                 */
/*   Updated: 2020/06/15 15:58:02 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* first step, print out PROMPT and allow for exit */

int	main(void)
{
  t_shell shell;
  char	*cmd;
  int i;

  ft_bzero(&shell, sizeof(shell));
  i = 1;
  while (i ==1)
  {
    print_prompt(shell);
    cmd = get_cmd(&shell);
    if (cmd)
      start_shell(&shell, cmd);
  }
  return (0);
}
