/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/14 15:36:44 by greed         #+#    #+#                 */
/*   Updated: 2020/10/06 14:47:33 by averheij      ########   odam.nl         */
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

enum			redirs
{
	IN,
	OUT,
};

enum			pipes
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

/* should put this struct into another one later, because it's just input, but im lazy rn */
typedef struct		s_data
{
	char			**argv;
	int				argc;
	t_list			*arg_lst;
	t_pid			pid;
	t_fd_sto		fd;
	char			**envp;
	int				redir_count;
	t_var			*env;
	t_cmd			*cmd;
}					t_data;

int					g_signal_exit;

/*
** FUNCTION PROTOTYPES
*/

void	put_error_data(t_data *data, char *error);
void	print_prompt();
void	reset_data(t_data *data);
void	fork_next_and_pipe(t_data *data, int is_parent);
void	cmd_dispatch(t_data *data);
void	wait_for_children(t_pid *pid);
char	*ft_3strjoin(const char *str1, const char *str2,
			const char *str3);
char	**free_array_null(char **str);
size_t	ft_strclen(const char *str, int c);
char	*get_path(void);
void	ft_reset_pid(t_pid *pid);
void	ft_add_pid(t_pid *pid, int add_value);
int		sto_fd(t_fd_sto *fd, int add_fd);
void	close_fd(t_fd_sto *fd, int io_fd[2]);

/*
** PARSING
*/

char	**list_to_string_array(t_list *to_copy);
char	*trim_spaces(char *res);
int		is_builtin(char *cmd);
void	parse_init(t_data *data);
int		parse_args(t_data *data, char *input);
bool	ft_env_char(int c, int first);
void	argv_env_replace(t_data *data);
char	*str_env_replace(t_data *data, char *str, int all);
char	*str_env_replace_index(t_data *data, char *str, int envstart);

int		parse_organize(t_data *data);
int		clear_cmd(t_cmd *cmd, void(*del)(void *));
int		drop_string(t_data *data, int i);
void	print_cmd_full(t_data *data);
void	print_cur_cmd(t_cmd *cmd);
void	set_signal(void);
bool	check_escape(char *str, int i);

/*
** BUILT-INS
*/

void	ft_exit();
void	ft_echo(t_cmd *cmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd, t_var *env);
void	ft_env(char **envp);
int		ft_exec(t_cmd *cmd, t_var *env, char **envp, t_pid *pid);
int 	error_builtin(t_cmd *cmd, int error);

/*
** ENV
*/

int		env_init(t_data *data);
char	*get_env_val(const char *name, t_var *env, size_t len);
int		clear_env(t_var *env, void(*del)(void *));
void	env_del(t_var *delete);

/*
** UNSET
*/

int		ft_unset(t_cmd *cmd, t_var **env);
int		unset_env(t_var **env, char *str);
void	update_env(t_data *data);
char	**convert_env(t_var *env);

/*
** EXPORT
*/

int		ft_export(t_cmd *cmd, t_var **env, char **envp);
void	env_set_val(const char *name, t_var **env, const char *val);
t_var	*env_add(const char *name, const char *val);
void	set_exit_env_val(t_var **env, int *last_status);

/*
** REDIRECTIONS
*/

void	redir_init(t_data *data);
void	redir_dispatch(t_fd_sto *fd, t_cmd *cmd, char *pipe);
void	redir_append(t_fd_sto *fd, t_cmd *cmd);
void	redir_trunc(t_fd_sto *fd, t_cmd *cmd);
void	redir_std_input(t_fd_sto *fd, t_cmd *cmd);
int		ft_is_redir(char *str);
void	open_pipe(t_fd_sto *fd, t_cmd *cmd);
void	set_fork_redir(t_cmd *cmd);
void	close_the_shit(t_data *data, t_cmd *cmd);

/*
** UTILITIES
*/

void	ft_free(void **free_me);
int		reset_prompt(t_data *data, char *error, int error_status, int all);
void	free_pid(t_pid *pid);
void	reset_data_struct(t_data *data, int all);

/*
** DEBUGGING
*/

void	print_vars(t_data *data);
void	print_list(t_list *list);
void	test_args(char  **argv, int argc);
void	print_environ(char **environ);
void	print_env(t_var *env);

#endif
