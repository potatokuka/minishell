#include "minishell.h"

/* if not CMD or REDIR, save that location of argv[i] to fd */

static int	check_redir(char *str)
{
	if (ft_strlen(str) == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			return (1);
		else
			return (0);
	}
	else if (ft_strlen(str) == 1)
	{
		if ((str[0] == '<') || (str[0] == '>'))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void		print_flags(char **flags)
{
	int	i;

	i = 0;
	perror("seg check 4");
	while (flags[i])
	{
		printf("flags= %d %s\n", i, flags[i]);
		i++;
	}
	perror("seg check 5");
	return ;
}

char		**save_redir(char **argv, int flags)
{
	char	**redir;
	int		i;
	int		x;

	i = 0;
	x = 0;
	printf("flags = %d\n", flags);
	redir = (char **)ft_calloc(sizeof(char *), flags);
	while (x < flags)
	{
		if (check_redir(argv[i]))
		{
			redir[x] = ft_strdup_lib(argv[i]);
			i++;
			x++;
			flags--;
		}
		else
			i++;
	}
	perror("seg check 3");
	return (redir);
}

/*
** run through all of the args to check if a flag is check
** malloc the each redir flag into a char array
*/

void		redir_init(t_input *inp)
{
	int		flags;
	int		i;

	flags = 0;
	i = 0;
	while (i < inp->argc) //inp->argv[i])
	{
		if (!check_redir(inp->argv[i]))
			i++;
		else
		{
			flags++;
			i++;
		}
	}
	if (flags)
	{
		printf("early flag check %d\n", flags);
		inp->redirs = save_redir(inp->argv, flags);
		perror("seg check 2");
		print_flags(inp->redirs);
		perror("seg check 6");
	}
	/* -- seg fault above this -- */
	perror("seg check 1");
	return ;
}
