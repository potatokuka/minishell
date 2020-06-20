/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 18:08:04 by greed         ########   odam.nl         */
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
# include <errno.h>
# include <string.h>

/*
**	Libft PrintF and Get Next Line Updated Lib List
*/

# include <libft.h>
# include <liblist.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define D_QOTE 34
# define S_QOTE 39
# define SPACE 32
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

typedef struct		s_var
{
	char			*name;
	char			*val;
	size_t			len;
	struct s_var	*next;
}					t_var;

/* should put this struct into another one later, because it's just input, but im lazy rn */
typedef struct		s_input
{
	char	*cmd;
	char	**argv;
	int		argc;
	int		echo_flag;
	t_list	*arg_lst;
	char	**envp;
	t_var	*env;
}			t_input;

/*
** FUNCTION PROTOTYPES
*/

void	print_prompt();
char	*get_cmd(t_input *inp);
void	parse_init(t_input *inp);
void	print_vars(t_input *inp);
void	print_list(t_list *list);
void	reset_input(t_input *input);
void	cmd_dispatch(t_input *inp);
void	ft_exit(t_input *inp);
void	ft_echo(t_input *inp);
void	ft_pwd(t_input *inp);
void	ft_cd(t_input *inp);
void	error_builtin(t_input *inp);

/*
** ENV
*/

int		env_init(t_input *inp);
char	*get_env_val(const char *name, t_var *env, size_t len);
int		clear_env(t_var *env, void(*del)(void *));
#endif
