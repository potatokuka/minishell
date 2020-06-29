/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/06/29 18:53:08 by averheij      ########   odam.nl         */
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
# include <sys/wait.h>

/*
**	Libft PrintF and Get Next Line Updated Lib List
*/

# include <libft.h>
# include <liblist.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PROMPT ">>: "
# define P_PMPT "\n>>: "

/*
** KEY CODES
*/

# define CTRL_D 4
# define CTRL_C 12
# define ESC 27
# define D_QOTE 34
# define S_QOTE 39
# define SPACE 32

/*
** STRUCTS
*/

typedef struct		s_redir
{
	char			**flags;
	int				**pos;
}					t_redir;

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
	t_list	*arg_lst;
	char	**envp;
	t_var	*env;
	char	**redirs;
}			t_input;

/*
** FUNCTION PROTOTYPES
*/

void	print_prompt();
void	reset_input(t_input *input);
void	cmd_dispatch(t_input *inp);
char	*ft_combine_str(const char *str1, const char *str2,
			const char *str3);
char	**free_array_null(char **str);
size_t	ft_strc_len(const char *str, int c);
char	*get_path(void);

/*
** PARSING
*/

int		is_cmd(char *cmd);
char	*get_cmd(t_input *inp);
char	*parse_cmd(t_input *inp, char *trimmed);
char	*del_leading_space(char *res);
void	parse_init(t_input *inp);
void	split_arg_lst(t_input *inp);
void	parse_args(t_input *inp, char *trimmed, int run_time);
void	repl_env_vars(t_input *inp);

/*
** BUILT-INS
*/

void	ft_exit(t_input *inp);
void	ft_echo(t_input *inp);
void	ft_pwd(t_input *inp);
void	ft_cd(t_input *inp);
void	ft_exec(t_input *inp);
void	ft_env(t_input *inp);
void	error_builtin(t_input *inp);

/*
** ENV
*/

int		env_init(t_input *inp);
char	*get_env_val(const char *name, t_var *env, size_t len);
int		clear_env(t_var *env, void(*del)(void *));
void	env_del(t_var *delete);

/*
** UNSET
*/

void	ft_unset(t_input *inp);
void	unset_env(t_var **env, char *str);
void	update_env(t_input *inp);
char	**convert_env(t_var *env);

/*
** EXPORT
*/

void	ft_export(t_input *inp);
t_var	*env_set_val(const char *name, t_var **env, const char *val);
t_var	*env_add(const char *name, const char *val);

/*
** REDIRECTIONS
*/

void	redir_init(t_input *inp);
void	redir_dispatch(t_input *inp);

/*
** DEBUGGING
*/

void	print_vars(t_input *inp);
void	print_list(t_list *list);
void	print_environ(char **environ);

#endif
