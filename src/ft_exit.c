#include "minishell.h"

void	ft_exit(t_shell *shell)
{
  free (shell->cmd);
  exit (0);
}
