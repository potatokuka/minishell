/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 11:35:20 by greed         #+#    #+#                 */
/*   Updated: 2020/06/16 11:35:29 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* print string after echo[DATA], but trim out quotes, if no quotes just print */

static void	print_echo(char *data, int len)
{
  char	*trim;
  int	i;

  i = 0;
  trim = NULL;
  perror("here");
  printf("%s\n", data);
  while (len)
  {
    if (data[i] != '"')
      trim[i] = data[i];
    len--;
  }
  ft_printf("\n%s\n%s", trim, PROMPT);
}

void		ft_echo(t_shell *shell, char *data)
{
  int	len;
  
  if (shell->init == 0)
    len = ft_strlen(data);
  if (data[0] == '"' && data[len] == '"')
    print_echo(data, len);

  return ;
}
