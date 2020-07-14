/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/07/14 19:44:58 by greed         ########   odam.nl         */
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

typedef struct		s_cmd
{
	char			*builtin;
	char			**argv;
	char			*pipe;
	char			*tar_file;
	int				argc;
	int				pipfd[2];
	int				pid1;
	t_list			*arr_list;
	struct s_cmd	*next;
	int				update_env;
}					t_cmd;

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
	char	**argv;
	int		argc;
	t_list	*arg_lst;
	char	**envp;
	t_var	*env;
	t_cmd	*cmd;
	char	**redirs;
}			t_input;

/*
** FUNCTION PROTOTYPES
*/

void	print_prompt();
void	reset_input(t_input *input);
void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp);
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
char	**list_to_chr_array(t_list *to_copy);
void	parse_args(t_input *inp, char *trimmed, int run_time);
void	repl_env_vars(t_input *inp);

int		parse_organize(t_input *inp);
int		clear_cmd(t_cmd *cmd, void(*del)(void *));
void	print_cmd_full(t_input *inp);
void	print_cur_cmd(t_cmd *cmd);
int		drop_string(t_input *inp, int i);

/*
** BUILT-INS
*/

void	ft_exit(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd, t_var *env);
void	ft_env(char **envp);
void	ft_exec(t_cmd *cmd, t_var *env, char **envp);
void	error_builtin(t_cmd *cmd);

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

void	ft_unset(t_cmd *cmd, t_var **env);
void	unset_env(t_var **env, char *str);
void	update_env(t_input *inp);
char	**convert_env(t_var *env);

/*
** EXPORT
*/

void	ft_export(t_cmd *cmd, t_var **env);
t_var	*env_set_val(const char *name, t_var **env, const char *val);
t_var	*env_add(const char *name, const char *val);

/*
** REDIRECTIONS
*/

void	redir_init(t_input *inp);
void	redir_dispatch(t_input *inp);
void	redir_append(t_input *inp);
void	redir_trunc(t_input *inp);
void	redir_std_input(t_input *inp);
int		ft_is_redir(char *str);
int		ft_is_valid_pipe(t_cmd *cmd);

/*
** DEBUGGING
*/

void	print_vars(t_input *inp);
void	print_list(t_list *list);
void	test_args(char  **argv, int argc);
void	print_environ(char **environ);

#endif
