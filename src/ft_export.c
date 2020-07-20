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

void	ft_export(t_cmd *cmd, t_var **env, char **envp)
{
	size_t	i;
	size_t	tmp;

	perror("INSIDE THE SHIT FOR EXPORT");
	printf("argc = %d\n", cmd->argc);
	if (cmd->argc == 0)
		return (ft_env(envp));
	perror("under");
	i = 0;
	while (cmd->argv[i])
	{
		printf("\t-- Export --\nargv[%zu]_%s\n", i, cmd->argv[i]);
		tmp = ft_strc_len(cmd->argv[i], '=');
		printf("\n\ntmp =_%zu\n", tmp);
		if (tmp < ft_strlen_lib(cmd->argv[i]))
		{
			if (ft_isdigit(cmd->argv[i][0]))
			{
				ft_printf("Export: %s: not a valid identifier\n", cmd->argv[i]);
				return ;
			}
			cmd->argv[i][tmp] = '\0';
			printf("testing argv[%zu]_%s\n%s\n", i, cmd->argv[i], &cmd->argv[i][tmp + 1]);
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
