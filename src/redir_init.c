#include "minishell.h"

void	redir_dispatch(t_cmd *cmd, char *pipe)
{
	if (cmd && pipe)
	{
		dprintf(2, "pipe =%s\n", pipe);
		if (ft_strcmp(pipe, ">>") == 0)
			redir_append(cmd);
		else if (ft_strcmp(pipe, "<") == 0)
			redir_std_input(cmd);
		else if (ft_strcmp(pipe, ">") == 0)
			redir_trunc(cmd);
	}
	return ;
}
