#include "minishell.h"

void	take_input(char *input)
{
	if (ft_strcmp(input, KILL) == 0)
		exit (0);
}

void	start_shell(t_shell *shell, char *cmd)
{
  if (shell->init == 0)
    ft_printf("testing cmd %s\n", cmd);
}
void	start_exit(int i)
{
  char data[128];
  if (i == 0)
  {
    read(0, data, 128);
    printf("%s\n", data);
    printf("%s\n", PROMPT);
    i++;
  }
return ;
}
