#include "minishell.h"

void	sig_handler_inp(int i)
{
	(void)i;
	ft_printf("\n");
	print_prompt();
	return ;
}
void	sig_handler(int i)
{
	(void)i;
	ft_printf("\n");
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, sig_handler_inp);
	signal(SIGINT, sig_handler_inp);
	signal(SIGSTOP, sig_handler_inp);
}
