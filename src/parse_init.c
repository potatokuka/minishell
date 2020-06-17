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

/* void	parse_args(t_input *inp, char *trimmed) */
/* { */
/*   char	*cmd_trim */
/*   int	i; */
/*   int	cmd_len; */

/*   cmd_len = ft_strlen(inp->cmd); */

/* } */

/*
** Saves from start of string to the first occurence of a non alpha 
** Null terminating the string
** Prepares trimmed for use in ARG
*/

char	*parse_cmd(t_input *inp, char *trimmed)
{
  int	i;

  i = 0;
  while (ft_isalpha(trimmed[i]))
    i++;
  inp->cmd = ft_strldup(trimmed, i);
  if (!inp->cmd)
    put_error("Invalid Command Given");
  while (i > 0)
  {
    trimmed++;
    i--;
  }
  return (trimmed);
}

/*
** Takes RES and returns a pointer to the next occurence of an alpha
*/

char	*del_leading_space(char *res)
{
  while (*res)
  {
    if (ft_isalpha(*res) != 1)
      res++;
    else
      break ;
  }
  return (res);
}

void	parse_input(t_input *inp, char *res)
{
  char	*trimmed;
  int	i;

  i = 0;
  trimmed = del_leading_space(res);
  trimmed = parse_cmd(inp, trimmed);
  if (trimmed) 
    parse_args(inp, trimmed);
  print_vars(inp);
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
