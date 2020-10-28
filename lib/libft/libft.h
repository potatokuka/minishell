/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:34:52 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 18:00:22 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strchr_lib(const char *s, int c);
size_t				ft_strlcpy_lib(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen_lib(const char *s);
char				*ft_strdup_lib(const char *s1);
char				*ft_substr_lib(char const *s, unsigned int start,
									size_t len);
char				*ft_strjoin_lib(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strldup(const char *src, size_t n);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

# ifndef NOLIST

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# endif

# ifndef NOLIST

void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
# endif

int					ft_strchr(char *s, int c);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *s);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
int					get_next_line(int fd, char **line);
int					pull_line(char **get, char **line, int c);

typedef struct		s_conv
{
	int				left;
	int				hash;
	int				padzero;
	int				width;
	int				precision;
	int				numlen;
	int				size;
	char			type;
	char			sign;
	int				len;
	char			hassign;
	char			neg;
	int				count;
	int				fd;
	unsigned int	u_numlen;
}					t_conv;
typedef void	(*t_cfunc)(t_conv *, va_list, int *);
typedef void	(*t_lfunc)(t_conv *, va_list, int *);

int					ft_printf(const char *input, ...);
void				ft_converter_link(t_conv *conv, va_list a_list, int *lv);
int					ft_printf_fd(int fd, const char *input, ...);
void				ft_putnbr_count_fd(int n, int fd, t_conv *conv, int *lv);
int					ft_nbr_size(int num);
void				ft_flag_check(const char **input, t_conv *conv);
void				ft_find_type(const char **input, t_conv *conv);
void				ft_flag_vars_set(t_conv *conv);
void				ft_print_char(t_conv *conv, va_list a_list, int *lv);
void				ft_print_string(t_conv *conv, va_list a_list, int *lv);
void				ft_print_pointer(t_conv *conv, va_list a_list, int *lv);
void				ft_print_int(t_conv *conv, va_list a_list, int *lv);
void				ft_print_uint(t_conv *conv, va_list a_list, int *lv);
void				ft_print_hex_lower(t_conv *conv, va_list a_list, int *lv);
void				ft_print_hex_upper(t_conv *conv, va_list a_list, int *lv);
void				ft_print_count(t_conv *conv, va_list a_list, int *lv);
void				ft_print_percent(t_conv *conv, va_list a_list, int *lv);
void				ft_pad_width(int width, int precision, int pad, int *lv);
void				ft_putstr_c_fd(char *str, int fd, int n, int *lv);
void				ft_putchar_c_fd(char c, int fd, int *lv);
void				ft_precision_check(const char **input, t_conv *conv);
void				ft_putnbr_c_fd(int n, int fd, t_conv *conv, int *lv);
void				ft_conv_dec(t_conv *conv, va_list a_list, int *lv);
void				ft_trunc_width(int n, int fd, t_conv *conv, int *lv);
void				ft_print_sign(int fd, t_conv *conv, int *lv);
void				ft_conv_int(t_conv *conv, int *num);
void				ft_intres_c_fd(int num, int *lv);
void				ft_print_uint(t_conv *conv, va_list a_list, int *lv);
unsigned int		ft_uint_size(unsigned int num);
void				ft_conv_uint(t_conv *conv, unsigned int num);
void				ft_u_intres_c_fd(unsigned int num, int *lv);
void				ft_print_x(t_conv *conv, va_list a_list, int *lv);
unsigned int		ft_x_size(unsigned int num);
void				ft_conv_x(t_conv *conv, unsigned int *num);
void				ft_x_res_c_fd(unsigned int num, int *lv);
void				ft_upx_res_c_fd(unsigned int num, int *lv);
void				ft_print_up_x(t_conv *conv, va_list a_list, int *lv);
void				ft_print_pct(t_conv *conv, va_list a_list, int *lv);
int					ft_valid_arg(const char **input, t_conv *conv);

/*
** THIS IS STUFF FOR SIZE BONUS
*/
void				ft_size_num(t_conv *conv, va_list a_list, int *lv);

/*
** Links for size
*/
void				ft_uint_link(t_conv *conv, va_list a_list, int *lv);
void				ft_int_link(t_conv *conv, va_list a_list, int *lv);
void				ft_x_link(t_conv *conv, va_list a_list, int *lv);
void				ft_up_x_link(t_conv *conv, va_list a_list, int *lv);

/*
** LL
*/

void				ft_conv_ll_int(t_conv *conv, long long int num);
long long int		ft_ll_nbr_size(long long int num);
void				ft_llint_c_fd(long long int num, int *lv);
void				ft_ll_num(t_conv *conv, va_list a_list, int *lv);

/*
** xX
*/

void				ft_print_ll_x(t_conv *conv, va_list a_list, int *lv);
int					ft_x_ll_size(unsigned long long num);
void				ft_x_res_ll_c_fd(unsigned long long num, int *lv);
void				ft_conv_ll_x(t_conv *conv, unsigned long long *num);
void				ft_ll_x(t_conv *conv, va_list a_list, int *lv);
void				ft_print_ll_up_x(t_conv *conv, va_list a_list, int *lv);
void				ft_upx_res_ll_c_fd(unsigned long long num, int *lv);

/*
** LLU
*/

void				ft_llu(t_conv *conv, va_list a_list, int *lv);
void				ft_llu_num(t_conv *conv, va_list a_list, int *lv);
void				ft_lluint_c_fd(unsigned long long num, int *lv);
int					ft_llu_nbr_size(unsigned long long num);
void				ft_conv_llu_int(t_conv *conv, unsigned long long num);

/*
** Pointers
*/

void				ft_print_pointer(t_conv *conv, va_list a_list, int *lv);
unsigned long		ft_ptr_size(unsigned long ptr);
void				ft_conv_ptr(t_conv *conv, unsigned long ptr);
void				ft_ptr_res_fd(unsigned long ptr, int *lv);

/*
** Cub3d Libs
*/

void				put_error(char *error);
#endif
