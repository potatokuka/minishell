#include "minishell.h"

char	*ft_save_qu_str(t_input *inp, char *trimmed, char quote)
{
	char	*tmp;
	int		i;
	int		q_count;
	int		skip;

	i = 0;
	q_count = 0;
	skip = 0;
	/* TODO start here, find the first occurance of quote, when finding this quote, */
	/* 	send to drop char, drop the two quotes, saving everything inside the quotes */
	/* 	check to see if there is anything after the last quote. if there is anything */
	/* 	left over after the quote continue to save this until a space, ALWAYS searching */
	/* 	for another occurance of a new pair of quotes. If no quote is founnd add what was */
	/* 	found until the space OR '\0' to back */
	while (*trimmed && trimmed[i] != '\0')
	{
		if (trimmed[i] == quote)
	}
}

char	*ft_save_quote(t_input *inp, char *trimmed, char quote)
{
	trimmed = ft_save_qu_str(inp, trimmed, quote)
	return (trimmed);
}
