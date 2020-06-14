#include "minishell.h"

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
