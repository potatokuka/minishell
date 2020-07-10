#include "minishell.h"

void	redir_dispatch(t_input *inp)
{
	printf("INSIDE OF REDIR_DISPATCH\n");
	if (inp->cmd && inp->cmd->pipe)
	{
		printf("pipe =%s\n", inp->cmd->pipe);
		if (ft_strncmp(inp->cmd->pipe, ">>", 2) == 0)
			redir_append(inp);
		/* else if (ft_strncmp(inp->redirs[i], "<", 1)) */
		/* 	redir_std_input(inp); */
		/* else if (ft_strncmp(inp->redirs[i], ">", 1)) */
		/* 	redir_std_out(inp); */
	}
	return ;
}
