#include "minishell.h"

/*
** Set a storage amount for initial path size, if the path is too large
** Set a larger path size
*/ 
void	ft_pwd(t_input *inp)
{
	char	*res;
	char	*path;
	size_t	size;

	size = 20;
	printf("inside pwd\n");
	(void)inp;
	path = malloc(sizeof(char) * (size + 1));
	if (!path)
		put_error("Error Inside of PWD");
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			put_error("Error Inside of PWD");
		res = getcwd(path, size + 1);
	}
	if (res)
		ft_printf("%s\n", path);
	free(path);
}
