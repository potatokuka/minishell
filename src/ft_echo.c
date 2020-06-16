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

void	print_echo(char *temp)
{
  ft_printf("%s\n", temp);
  return ;
}

void	ft_echo(t_shell *shell)
{
 /* set a tmp *char to hold shell->data realloc for the printable str */ 
  char	*temp;
  int	print_len;
  int	start;
  int	end;
  int	i;
  
  start = 0;
  end = ft_strlen(shell->data);
  temp = NULL;
  i = 0;
  print_len = 0;
  printf("INSIDE OF THIS%s\n", shell->data);
  perror("here");
  while (shell->data[start] != 34)
    start++;
  perror("maybe");
  while (shell->data[end] != 34)
    end--;
  /* print_len = (end -  start) + 1; */
  perror("there");
  while (start < end)
  {
    perror("this");
    temp[i] = shell->data[start];
    i++;
    start++;
  }
  temp[i] = '\0';
  ft_printf("\n%s", temp);
  /* print_echo(temp); */
  return ;
}
