#include "minishell.h"

void	env_del(t_var *delete)
{
	free(delete->name);
	free(delete->val);
	free(delete);
}
