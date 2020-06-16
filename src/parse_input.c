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

void	parse_input(t_shell *shell, char *input)
{
  char	*clean;
  char	*temp;
  int	len;
  int	i;

  i = 0;
  len = ft_strlen(input);
  clean = malloc(sizeof(char) * len);

}
