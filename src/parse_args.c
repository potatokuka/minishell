/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/21 11:07:59 by greed         #+#    #+#                 */
/*   Updated: 2020/07/14 19:46:13 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** need to trim spaces until first non ' '
** CMD == from first CHAR -> ' '
** after this is saved, the DATA input NEEDS to be trim
** EVERY ' ' EXCEPT the FIRST one AFTER the last CHAR
*/

/* 
** split arg_lst into argc argv for easier access
*/

int		ft_env_char(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

/*
** When triggered by a '$', save through to the next '$' || '\0' || ' '
** IF the characters inside != UPPER CASE APHLA dont save shit inside
*/

char	*ft_save_dolla(t_input *inp, char *trimmed, int start)
{
	char	*str;
	int		i;
	int		skip;

	skip = 0;
	i = 0;
	while (trimmed[start] != '$' && trimmed[start] != ' ' &&
				trimmed[start] != '\0')
	{
		if (ft_env_char(trimmed[start]) == 0)
			skip = 1;
		i++;
		start++;
	}
	if (skip == 0)
	{
		str = ft_strldup(trimmed, i + 1);
		if (!str)
			put_error("Error in arguement parsing");
		printf("STR $ check =_%s_\n", str);
		if (*str)
		{
			inp->argc += 1;
			lst_new_back(&inp->arg_lst, str);
		}
	}
	trimmed = trimmed + i + 1;
	return (trimmed);
}

/*
** check the pipe TYPE and save it, if REDIR type, save target file and
** move pointer forward ALSO MOVE INTO CMD->NEXT
*/

void	drop_char(char *trim, char c, int count)
{
	int		writer;
	int		reader;
	int		post_count;

	post_count = 0;
	writer = 0;
	reader = 0;
	while (trim[reader])
	{
		if (trim[reader] == c && post_count < count)
		{
			reader++;
			post_count += 1;
		}
		trim[writer] = trim[reader];
		writer++;
		reader++;

	}
	trim[writer] = 0;
}

char	*ft_save_qu_str(t_input *inp, char *trimmed, int start, char quote, char *test)
{
	char	*tmp;
	char	*str;
	int		i;
	int		q_count;
	int		skip;

	i = 0;
	q_count = 0;
	skip = 0;
	/* at this point, all spaces before are already trimmed */
	while (q_count < 2 && test[i] != '\0')
	{
		if (test[i] == quote)
			q_count += 1;
		i++;
	}
	drop_char(test, quote, 2);
	printf("\t\ttest_%s i = %d\n", test, i);
	while (test[i] != '\0' && test[i] != ' ')
	{
		if (test[i] == D_QOTE || test[i] == S_QOTE)
		{
			drop_char(test, test[i], 2);
		}
		i++;
	}
	tmp = ft_strldup(test, i);
	if (!tmp)
		put_error("Error in arg parser 1");
	if (*tmp)
	{
		inp->argc += 1;
		lst_new_back(&inp->arg_lst, tmp);
	}
	printf("\t\tFINAL TEMP TEST =_%s\n", tmp);
	skip += ft_strlen(tmp);
	printf("trimmed b4_%s\n", trimmed);
	trimmed += (skip + 1);
	printf("trimmed after_%s\n", trimmed);
	/* exit(1); */
	return (trimmed);
}
/*
** check starting pos, see what the char is there Quote or Dquote
** save from +1 of start until next occurence of Quote
*/

// TODO IF HAS SPACE, IS TRIGGERED does normal save, if it's not triggered need
// TODO work out how to correctly save test, BEFORE " and then join the two
// TODO CHECK before exit of save quote for last QUOTE + 1, if it is a non space
// TODO save the next string until '/0' or ' '
char	*ft_save_quote(t_input *inp, char *trimmed, int start, char quote, char *test)
{
	trimmed = ft_save_qu_str(inp, trimmed, start, quote, test);
	return (trimmed);
}

/*
** save until non alpha into args[i]
** IF read a Quote or Dquote send to save with quotes
** del_leading_space after each arg is saved
** maybe can do this recursively
** save everything from SP to SP, SP is 32 in ascii dec
** EASIER WAY, save each arg into linked list, split into array
** after it's fully finished
*/

void	parse_args(t_input *inp, char *trimmed)
{
	char	*str;
	int		i;

	i = 0;
	if (!trimmed)
		return ;
	trimmed = del_leading_space(trimmed);
	while (trimmed[i] != ' ' && trimmed[i] != '\0')
	{
		if (trimmed[i] == D_QOTE || trimmed[i] == S_QOTE)
			trimmed = ft_save_quote(inp, (trimmed + 1), i, trimmed[i], trimmed);
		else if (trimmed[i] == '$')
			trimmed = ft_save_dolla(inp, trimmed, (i + 1));
		else
			i++;
	}
	str = ft_strldup(trimmed, i);
	if (!str)
		put_error("Error in arguement parsing");
	if (*str)
	{
		inp->argc += 1;
		lst_new_back(&inp->arg_lst, str);
	}
	trimmed = trimmed + i;
	if (*trimmed)
		parse_args(inp, trimmed);
}
