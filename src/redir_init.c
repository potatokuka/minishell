#include "minishell.h"

void	redir_dispatch(t_data *data)
{
	if (data->cmd && data->cmd->pipe)
	{
		dprintf(2,"pipe =%s\n", data->cmd->pipe);
		if (ft_strcmp(data->cmd->pipe, ">>") == 0)
			redir_append(data);
		else if (ft_strcmp(data->cmd->pipe, "<") == 0)
			redir_std_input(data);
		else if (ft_strcmp(data->cmd->pipe, ">") == 0)
			redir_trunc(data);
	}
	return ;
}
