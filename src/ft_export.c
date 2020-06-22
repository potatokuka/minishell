#include "minishell.h"

void	ft_export(t_input *inp)
{
	size_t	i;
	size_t	tmp;

	if (inp->argc < 1)
		return ;
	i = 0;
	while (inp->argv[i])
	{
		tmp = ft_strc_len(inp->argv[i], '=');
		if (tmp < ft_strlen_lib(inp->argv[i]))
		{
			inp->argv[i][tmp] = '\0';
			(void)env_set_val(inp->argv[i], &inp->env,
					&inp->argv[i][tmp + 1]);
		}
		i++;
	}
	update_env(inp);
}
