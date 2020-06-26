#include "minishell.h"

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
	size_t	x;

	i = 0;
	x = 0;
	printf("flags = %d\n", flags);
	redir = (char **)malloc(sizeof(char *) * flags);
	while (argv[i])
	{
		if (check_redir(argv[i]))
		{
			printf("Flag Check = %s\n", argv[i]);
			redir[x] = (char *)malloc(sizeof(char) * ft_strlen(argv[i] + 1));
			i++;
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
	if (flags)
	{
		printf("early flag check %d\n", flags);
		inp->redirs = save_redir(inp->argv, flags);
		print_flags(inp->redirs);
	}
	return ;
}
