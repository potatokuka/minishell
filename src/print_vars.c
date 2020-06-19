#include "minishell.h"

void	print_args(t_input *inp)
{
	int	y;

	y = 0;
	printf("--------\nPRINTING ARGS\nARGC = %d\n", inp->argc);
	while (y < inp->argc)
	{
		printf("%s\n", inp->argv[y]);
		y++;
	}
}

void	print_vars(t_input *inp)
{
	ft_printf("CMD = %s\n", inp->cmd);
	print_args(inp);
}
