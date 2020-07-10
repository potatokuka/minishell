#include "minishell.h"

void	redir_dispatch(t_input *inp)
{
	printf("INSIDE OF REDIR_DISPATCH\n");
	if (inp->cmd && inp->cmd->pipe)
	{
		printf("pipe =%s\n", inp->cmd->pipe);
		if (ft_strcmp(inp->cmd->pipe, ">>") == 0)
			redir_append(inp);
		else if (ft_strcmp(inp->cmd->pipe, "<") == 0)
			redir_std_input(inp);
		else if (ft_strcmp(inp->cmd->pipe, ">") == 0)
			redir_trunc(inp);
	}
	return ;
}
