#include "minishell.h"

static int	check_redir(char *str)
{
	if (ft_strncmp(str[i], "<") || ft_strncmp(str[i], ">"))
		return (1);
	return (0);
}

char		**save_redir(char **argv, int flags)
{
	char	**redir;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	redir = (char **)malloc(sizeof(char *) * flags);
	while (argv[i] && flags)
	{
		if (check_redir(argv[i]))
		{
			redir[x] = (char *)malloc(sizeof(char) * ft_strlen(argv[i] + 1));
			i++;
			flags--;
			x++;
		}
		else
			i++;
	}
	return (redir);
}

/*
** run through all of the args to check if a flag is check
** malloc the each redir flag into a char array
*/

void		redir_init(t_input *inp)
{
	size_t	flags;
	size_t	i;

	flags = 0;
	while (i < inp->argc)
	{
		if (!check_redir(inp->argv[i]))
		{
			i++;
			argc--;
		}
		else
		{
			flags++;
			i++;
			argc--;
		}
	}
	if (flags)
		inp->redir = save_redir(inp->argv, flags);
	return ;
}
