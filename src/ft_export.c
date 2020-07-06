/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:09:44 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 14:38:30 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_cmd *cmd, t_var **env)
{
	size_t	i;
	size_t	tmp;

	if (cmd->argc < 1)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		tmp = ft_strc_len(cmd->argv[i], '=');
		if (tmp < ft_strlen_lib(cmd->argv[i]))
		{
			cmd->argv[i][tmp] = '\0';
			(void)env_set_val(cmd->argv[i], env,
					&cmd->argv[i][tmp + 1]);
		}
		i++;
	}
	t_var *envapwoidj;
	envapwoidj = *env;
	while (envapwoidj)
	{
		printf("	%s=%s\n", envapwoidj->name, envapwoidj->val);
		envapwoidj = envapwoidj->next;
	}
	cmd->update_env = 1;
}
