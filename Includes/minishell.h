/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/06/14 15:36:45 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
** KEY CODES
*/
# define CTRL_D 4
# define CTRL_C 12
# define ESC 27
# define CTRL 49
# define PROMPT ">>: "


/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <termios.h>

#endif
