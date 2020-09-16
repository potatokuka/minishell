/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/17 10:00:40 by greed         #+#    #+#                 */
/*   Updated: 2020/07/17 10:04:06 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	drop_char(char *trim, char c, int count)
{
	int		writer;
	int		reader;
	int		post_count;
	int		l1;
	int		l2;

	post_count = 0;
	writer = 0;
	reader = 0;
	l1 = ft_strlen(trim);
	l2 = 0;
	while (trim[reader] && trim[reader] != '\0')
	{
		/* printf("trim_reader_%c\n", trim[reader]); */
		if (trim[reader] == c && post_count < count)
		{
			reader++;
			post_count += 1;
		}
		trim[writer] = trim[reader];
		writer++;
		if (trim[reader])
			reader++;

	}
	if (post_count != 2)
		put_error("Unclosed quotations");
	printf("trim writer_%s\n", trim);
	trim[writer] = '\0';
}

char	*ft_save_qu_str(t_data *data, char *trimmed, int start, char quote, char *test)
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
/* ISSUE: trimmed is increase extra + 1 somewhere */
	printf("trimmed b3_%s\n", trimmed);
	while (q_count < 2 && test[i] != '\0')
	{
		if (test[i] == quote)
			q_count += 1;
		i++;
	}
	drop_char(test, quote, 2);
	i -= q_count;
	printf("\t\ttest_%s i = %d\n", test, i);
	while (test[i] != '\0' && test[i] != ' ')
	{
		if (test[i] == D_QOTE || test[i] == S_QOTE)
		{
			drop_char(test, test[i], 2);
		}
		printf("\n--**-- test[%d] =_%c --**--\n", i, test[i]);
		i++;
	}
	tmp = ft_strldup(test, i);
	printf("\t\tTEMP_%s i = %d TEMP i_%c\n", tmp, i, tmp[i]);
	if (!tmp)
		put_error("Error in arg parser 1");
	if (*tmp)
	{
		data->argc += 1;
		lst_new_back(&data->arg_lst, tmp);
	}
	printf("\t\tFINAL TEMP TEST =_%s\n", tmp);
	skip += ft_strlen(tmp + 1);
	printf("trimmed b4_%s\n", trimmed);
	trimmed += skip;
	printf("trimmed after_%s\n", trimmed);
	return (trimmed);
}

char	*ft_save_quote(t_data *data, char *trimmed, int start, char quote, char *test)
{
	trimmed = ft_save_qu_str(data, trimmed, start, quote, test);
	return (trimmed);
}
