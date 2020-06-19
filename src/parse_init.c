/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 22:10:35 by greed         #+#    #+#                 */
/*   Updated: 2020/06/19 15:18:16 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to trim spaces until first none ' ' */
/* CMD == from first CHAR -> ' ' */
/* after this is saved, the DATA input NEEDS to be trim */
/* EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR */

/* is ALPHA returns 1 when reading an ALPHA */

char	*del_leading_space(char *res)
{
	while (*res)
	{
		if (ft_isalpha(*res) != 1)
			res++;
		else
			break ;
	}
	return (res);
}

char	*del_lead_arg(char *res)
{
	while (*res)
	{
		if (*res == ' ')
			res++;
		else
			break ;
	}
	return (res);
}

/* split arg_lst into argc argv for easier access */
void	split_arg_lst(t_input *inp)
{
	char	**tmp;
	char	*str;
	t_list	*lst;
	int		size_len;
	int		x;

	x = 0;
	size_len = lst_size(inp->arg_lst);
	printf("\nLST SIZE = %d\n", size_len);
	inp->argc = size_len;
	tmp = (char **)malloc(sizeof(char *) * size_len);
	lst = inp->arg_lst;
	while (x < size_len)
	{
		str = lst->content;
		tmp[x] = ft_strdup_lib(str);
		lst = lst->next;
		x++;
	}
	inp->argv = tmp;
	print_vars(inp);
}

/* check starting pos, see what the char is there Quote or Dquote */
/* save from +1 of start until next occurence of Quote */

void	ft_save_quote(t_input *inp, char *trimmed, int start, char quote)
{
	char	*str;
	int	i;

	i = 0;
	trimmed += 1;
	while (trimmed[start] != quote && trimmed[start])
		i++;
	str = ft_strldup(trimmed, i);
	if (*str)
	{
		printf("trimmed arg		_%s\n", str);
		lst_new_back(&inp->arg_lst, str);
		printf("just added to back of list:%p\n", inp->arg_lst);
		print_list(inp->arg_lst);
	}
	return ;
}

/* save until non alpha into args[i] */
/* IF read a Quote or Dquote send to save with quotes */
/* del_leading_space after each arg is saved */
/* maybe can do this recursively */
/* save everything from SP to SP, SP is 32 in ascii dec */
		/* ------------------------- */
/* EASIER WAY, save each arg into linked list, split into array */
/* after it's fully finished */

void	parse_args(t_input *inp, char *trimmed, int run_time)
{
	char	*str;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	perror("start of parse_args");
	printf("depth:%d\ntrimmed before del	_%s\n", run_time, trimmed);
	trimmed = del_lead_arg(trimmed);
	/* this works \/\/\/\/ */
	printf("trimmed after del	_%s\n", trimmed);
	while (trimmed[i] != ' ' && trimmed[i] != '\0')
	{
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
			ft_save_quote(inp, trimmed, (i + 1), trimmed[i]);
		else
			i++;
	}
	str = ft_strldup(trimmed, i);
	if (*str)
	{
		printf("trimmed arg		_%s\n", str);
		lst_new_back(&inp->arg_lst, str);
		printf("just added to back of list:%p\n", inp->arg_lst);
		print_list(inp->arg_lst);
		/*free(str);*/
	}
	run_time++;
	if (trimmed[i + 1])
	{
		trimmed = trimmed + i;
		parse_args(inp, trimmed, run_time);
		return ;
	}
}

/*
** Saves from start of string to the first occurence of a non alpha 
** Null terminating the string
** Prepares trimmed for use in ARG
*/

char	*parse_cmd(t_input *inp, char *trimmed)
{
	int	i;

	i = 0;
	while (ft_isalpha(trimmed[i]))
		i++;
	inp->cmd = ft_strldup(trimmed, i);
	if (!inp->cmd)
		put_error("Invalid Command Given");
	trimmed = trimmed + i;
	return (trimmed);
}

/*
** Takes RES and returns a pointer to the next occurence of an alpha
*/

void	parse_input(t_input *inp, char *res)
{
	char	*trimmed;

	trimmed = del_leading_space(res);
	trimmed = parse_cmd(inp, trimmed);
	if (trimmed)
		parse_args(inp, trimmed, 0);
	printf("about to go into split arg:%p\n", inp->arg_lst);
	print_list(inp->arg_lst);
	split_arg_lst(inp);
	print_vars(inp);
	printf("Trimmed = %s\n", trimmed);
}

void	parse_init(t_input *inp)
{
	char	*res;

	(void)inp;
	if (get_next_line(STDIN, &res) < 0)
		put_error("Invalid input read");
	parse_input(inp, res);
	/* exit(0); */
}
