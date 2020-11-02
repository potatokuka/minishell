/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/11/02 17:29:13 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*
**	Libft PrintF and Get Next Line Updated Lib List
*/

# include <libft.h>
# include <liblist.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define READ 0
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
** ENUMS
*/

enum				e_redirs
{
	IN,
	OUT,
};

enum				e_pipes
{
	READ_FD,
	WRITE_FD,
};

/*
** STRUCTS
*/

typedef struct		s_redir
{
	char			**flags;
	int				**pos;
}					t_redir;

typedef	struct		s_pid
{
	int				count;
	int				*value;
	int				last_status;
}					t_pid;

typedef struct		s_fd_sto
{
	int				*arr;
	int				mem;
	int				used;
}					t_fd_sto;

typedef struct		s_cmd
{
	char			*builtin;
	char			**argv;
	char			*tar_file;
	int				argc;
	int				io_fd[2];
	int				pipe_read_end;
	int				resetfd[2];
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

typedef struct		s_data
{
	char			**argv;
	char			**argv_head;
	int				argc;
	t_list			*arg_lst;
	t_pid			pid;
	t_fd_sto		fd;
	char			**envp;
	t_var			*env;
	t_cmd			*cmd;
	t_cmd			*forked;
	char			*input_leftovers;
	char			*input_head;
	int				had_quote;
}					t_data;

int					g_signal_exit;
int					g_prompt_printed;
int					g_is_parent;

/*
** FUNCTION PROTOTYPES
*/

void				put_error_data(t_data *data, char *error);
void				*reset_prompt_cmd(t_data *data, t_cmd *cmd, char *fterror,
							int error_val);
void				print_prompt();
void				reset_data(t_data *data);
void				fork_next_and_pipe(t_data *data, t_cmd *cmd, int is_parent);
void				cmd_dispatch(t_data *data, t_cmd *cmd, int is_child);
void				wait_for_children(t_pid *pid, int parent_exec);
char				*ft_3strjoin(const char *str1, const char *str2,
						const char *str3);
char				**free_array_null(char **str);
size_t				ft_strclen(const char *str, int c);
int					get_path(char **res);
void				ft_reset_pid(t_pid *pid);
int					ft_add_pid(t_pid *pid, int add_value);
int					sto_fd(t_fd_sto *fd, int add_fd);
void				close_fd(t_fd_sto *fd, int io_fd[2]);
t_cmd				*add_forked_cmd(t_data *data, t_cmd *cmd);
void				free_fd(t_fd_sto *fd);
void				free_var(t_var *env);
int					dup_redir(t_cmd *cmd, int is_child);
void				put_error_data_cmd(t_data *data, t_cmd *cmd, char *error);

/*
** PARSING
*/

char				**list_to_string_array(t_list *to_copy);
char				*trim_spaces(char *res);
int					is_builtin(char *cmd);
void				parse_init(t_data *data);
int					parse_args(t_data *data, char *input);
bool				ft_env_char(int c, int first);
void				argv_env_replace(t_data *data);
char				*str_env_replace(t_data *data, char *str);
char				*str_env_replace_index(t_data *data, char *str,
						int envstart);
int					file_match(char file[], char *file2);

int					parse_organize(t_data *data);
int					clear_cmd(t_cmd **cmd);
int					drop_string(t_data *data, int i);
void				set_signal(void);
bool				check_escape(char *str, int i);
t_cmd				*split_init(t_data *da);
void				convert_esc(t_data *data, t_cmd *new, char *arg, int index);
int					has_escape(char *str);
char				*convert_esc2(char *arg, char *tmp, int i, int x);
t_cmd				*save_in_pipe(t_data *data, t_cmd *new, int i);
t_cmd				*save_in_semi(t_data *data, t_cmd *new, int i);
t_cmd				*save_in_flag(t_data *data, t_cmd *new, int i);
char				*arg(t_data *dt, char *in, char *break_chars, int quote);
int					add_arg(t_data *data, char *arg, char *input);

char				*safe_strljoin(char *s1, ssize_t l1, char *s2,
						t_data *data);
char				*safestrjn(char *s1, char *s2);
int					escset(char *input, char *set, int i);
int					iscset(char c, char *set);
char				*ft_strljoin(char const *s1, ssize_t l1, char const *s2,
						ssize_t l2);
int					check_quotes_closed(char *input, int *i);
char				*handle_escapes_envs(t_data *da, char *arg, int substitute, int no_quote);
char				*handle_escape_quotes(char *arg);
bool				check_escape(char *str, int i);
void				*free_ret_null(char *free_me);

/*
** BUILT-INS
*/

int					ft_exit(t_cmd *cmd, int	last_status);
void				ft_echo(t_cmd *cmd);
int					ft_pwd(void);
int					ft_cd(t_cmd *cmd, t_var *env);
void				ft_env(char **envp);
int					ft_exec(t_cmd *cmd, t_var *env, char **envp, t_pid *pid);
int					error_builtin(t_cmd *cmd, int error);

/*
** ENV
*/

int					env_init(t_data *data);
char				*get_env_val(const char *name, t_var *env, size_t len);
int					clear_env(t_var *env, void(*del)(void *));
void				env_del(t_var *delete);

/*
** UNSET
*/

int					ft_unset(t_cmd *cmd, t_var **env);
int					unset_env(t_var **env, char *str);
void				update_env(t_data *data);
char				**convert_env(t_var *env);

/*
** EXPORT
*/

int					ft_export(t_cmd *cmd, t_var **env, char **envp);
int					env_set_val(const char *name, t_var **env, const char *val);
t_var				*env_add(const char *name, const char *val);
int					set_exit_env_val(t_var **env, int *last_status);

/*
** REDIRECTIONS
*/

int					redir_dispatch(t_data *data, t_fd_sto *fd, t_cmd *cmd,
						char *pipe);
int					redir_append(t_data *data, t_fd_sto *fd, t_cmd *cmd);
int					redir_trunc(t_data *data, t_fd_sto *fd, t_cmd *cmd);
int					redir_std_input(t_data *data, t_fd_sto *fd, t_cmd *cmd);
int					ft_is_redir(char *str);
int					open_pipe(t_fd_sto *fd, t_cmd *cmd);
void				set_fork_redir(t_cmd *cmd);
int					close_the_shit(t_cmd *cmd);

/*
** UTILITIES
*/

void				ft_free(void **free_me);
int					reset_prompt(t_data *data, char *error, int error_status,
						int all);
void				free_pid(t_pid *pid);
void				free_cmd(t_cmd *cmd);
void				reset_data_struct(t_data *data, int all);
char				**free_data_argv(t_data *data);

/*
** DEBUGGING
*/

#endif
