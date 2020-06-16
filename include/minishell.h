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

typedef struct		s_shell
{
  char	*cmd;
  char	*data;
  int	init;
  int	vars;
}			t_shell;

/*
** FUNCTION PROTOTYPES
*/

void	start_exit(int i);
void	print_prompt();
void	start_shell(t_shell *shell, char *cmd);
char	*get_cmd(t_shell *shell);
void	ft_echo(t_shell *shell, char *data);

#endif
