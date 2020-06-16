#include "minishell.h"

void	save_data(t_shell *shell, char *input)
{
  /* count until the first char, skip over all spaces until then, after that dont skip a space */
  int	start;
  int	len;
  int	i;
  int	in_len;

  i = 0;
  start = 0;
  in_len = 0;
  len = ft_strlen(input);
  /* skip over CMD */
  while (input[start] != ' ')
    start++;
      while (input[start] == ' ')
	start++;
  in_len = len - start;
  shell->data = (char *)malloc(sizeof(char) * in_len);
  while (start < len)
  {
    shell->data[i] = input[start];
    i++;
    start++;
  }
  shell->data[i] = '\0';
  return ;
}

void	save_cmd(t_shell *shell, char *input, int in_len)
{
  /* need to len res, input until ' ', and malloc for that */
  int	i;
  int	len;
  /* res = NULL; */
  i = 0;
  len = 0;
  while (input[len] != ' ')
    len++;
  if (in_len == len)
    shell->vars = 1;
  shell->cmd = (char *)malloc(sizeof(char) * len);
  while (i < len)
  {
    shell->cmd[i] = input[i];
    i++;
  }
  shell->cmd[i] = '\0';
  return ;
}

void		start_shell(t_shell *shell, char *sent)
{
  char	*input;
  int	len;
  int	dont_ret;

  dont_ret = 0;
  len = ft_strlen(sent);
  input = (char *)malloc(sizeof(char) * len);
  
  input = sent;
  save_cmd(shell, input, len);
  if (shell->vars != 1) 
    save_data(shell, input);
  printf("cmd = %s data = %s\n", shell->cmd, shell->data);
  cmd_dispatch(shell);
  free (input);
  /* free (input); */
  /* if (dont_ret == 1) */
   /* return ; */
  /* shell->data = save_data(input); */
  /* printf("Test CMD %s | Test DATA %s\n", shell->cmd, shell->data); */
}
