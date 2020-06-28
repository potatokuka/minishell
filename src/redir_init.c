#include "minishell.h"

/* if not CMD or REDIR, save that location of argv[i] to fd */

static int	check_redir(char *str)
{
	if (ft_strlen(str) == 2)
	{
		perror("2");
		if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
			return (1);
		else
			return (0);
	}
	else if (ft_strlen(str) == 1)
	{
		perror("1");
		if ((str[0] == '<') || (str[0] == '>'))
			return (1);
		else
			return (0);
	}
	else
	{
		perror("no match");
		return (0);
	}
}

void		print_flags(char **flags)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		printf("flags %d %s\n", i, flags[i]);
		i++;
	}
	return ;
}

char		**save_redir(char **argv, int flags)
{
	char	**redir;
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	printf("flags = %d\n", flags);
	redir = (char **)ft_calloc(sizeof(char *), flags);
	while (x < flags)
	{
		if (check_redir(argv[i]))
		{
			printf("Flag Check = %s\n", argv[i]);
			redir[x] = ft_strdup_lib(argv[i]);
			i++;
			x++;
			flags--;
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
	int		flags;
	int		i;

	flags = 0;
	i = 0;
	while (inp->argv[i])
	{
		if (!check_redir(inp->argv[i]))
			i++;
		else
		{
			flags++;
			i++;
		}
	}
	/* The seg fault is above this ^^^ */
	perror("seg check 1");
	if (flags)
	{
		printf("early flag check %d\n", flags);
		inp->redirs = save_redir(inp->argv, flags);
		print_flags(inp->redirs);
	}
	return ;
}
