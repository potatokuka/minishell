/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:49 by greed         #+#    #+#                 */
/*   Updated: 2020/10/29 14:25:29 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*add_forked_cmd(t_data *data, t_cmd *cmd)
{
	t_cmd	*i;
	t_cmd	*temp;

	temp = cmd->next;
	cmd->next = NULL;
	if (!data->forked)
		data->forked = cmd;
	else
	{
		i = data->forked;
		while (i->next)
			i = i->next;
		i->next = cmd;
	}
	i = data->forked;
	return (temp);
}

int		ft_add_pid(t_pid *pid, int add_value)
{
	int		i;
	int		*tmp_value;

	tmp_value = ft_calloc(sizeof(int), pid->count + 2);
	if (!tmp_value)
		return (1);
	i = 0;
	while (i < pid->count)
	{
		tmp_value[i] = pid->value[i];
		i++;
	}
	pid->count += 1;
	tmp_value[i] = add_value;
	ft_free((void **)&pid->value);
	pid->value = tmp_value;
	return (0);
}

int		ft_is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else
		return (0);
}

size_t	ft_strclen(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}
