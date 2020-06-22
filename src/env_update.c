#include "minishell.h"

char	**free_array_null(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	update_env(t_input *inp)
{
	free_array_null(inp->envp);
	inp->envp = convert_env(inp->env);
	if (!inp->envp)
		return (void)(clear_env(inp->env, &free));
}
