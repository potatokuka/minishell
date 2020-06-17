/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/06/16 22:10:43 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to trim spaces until first none ' ' */
/* CMD == from first CHAR -> ' ' */
/* after this is saved, the DATA input NEEDS to be trim */
/* EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR */

/* is ALPHA returns 1 when reading an ALPHA */
void	terminate_str(char *str, int len)
{
  str[len] = '\0';
  return ;
}

void	parse_cmd(t_input *inp, char *trimmed)
{
  int	i;

  i = 0;
  while (*trimmed)
  {
    if (ft_isalpha(trimmed[i]) == 1)
      i++;
    else
      break ;
  }
  printf("i = %d trimmed test = %s\n", i, trimmed);
  inp->cmd = (char *)malloc(sizeof(char) * i + 1);
  i = 0;
  while (*trimmed)
  {
    if (ft_isalpha(trimmed[i] == 1))
    {
      inp->cmd[i] = trimmed[i];
      i++;
    }
    else
      break ;
  }
  inp->cmd[i + 1] = '\0';
  printf("i = %d Trimmed cmd = %s\n", i, inp->cmd);
  return ;
}

char	*del_leading_space(char *res)
{
  while (*res)
  {
    if (ft_isalpha(*res) != 1)
      res++;
    else
      break ;
  }
  printf("RES = %s\n", res);
  return (res);
}

void	parse_input(t_input *inp, char *res)
{
  char	*trimmed;
  int	i;

  i = 0;
  trimmed = del_leading_space(res);
  parse_cmd(inp, trimmed);
  printf("Trimmed = %s\n", trimmed);
}

void	parse_init(t_input *inp)
{
  char	*res;
  
  (void)inp;
  if (get_next_line(STDIN, &res) < 0)
    put_error("Invalid input read");
  parse_input(inp, res);
}
