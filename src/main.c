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
  t_input inp;
  int i;

  ft_bzero(&inp, sizeof(inp));
  i = 1;
  while (i ==1)
  {
    print_prompt(&inp);
    parse_init(&inp);
  }
  return (0);
}
