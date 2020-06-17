/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/06/16 11:35:52 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>

/*
**	Libft PrintF and Get Next Line Updated Lib List
*/

# include <libft.h>
# include <liblist.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
** KEY CODES
*/

# define CTRL_D 4
# define CTRL_C 12
# define ESC 27
# define PROMPT ">>: "
# define P_PMPT "\n>>: "
# define KILL "exit"

/*
** STRUCTS
*/

typedef struct		s_input
{
  char	*cmd;
  char	**argv;
  int	argc;
}			t_input;

/*
** FUNCTION PROTOTYPES
*/

void	print_prompt();
char	*get_cmd(t_input *inp);
void	parse_init(t_input *inp);

#endif
