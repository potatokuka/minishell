#include "minishell.h"

void	env_del(t_var *delete)
{
	perror("env del");
	free(delete->name);
	free(delete->val);
	free(delete);
}
