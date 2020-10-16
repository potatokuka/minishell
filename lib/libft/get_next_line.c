/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/29 20:39:13 by greed         #+#    #+#                 */
/*   Updated: 2020/10/16 14:21:17 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		pull_line(char **get, char **line, int c)
{
	char			*temp;

	*line = ft_substr(*get, 0, ft_strchr(*get, c) - ((c == '\0') ? -1 : +1));
	if (c == '\0')
	{
		free(*get);
		*get = NULL;
		return (0);
	}
	temp = ft_substr(*get, ft_strchr(*get, c),
		ft_strlen(*get) - ft_strchr(*get, c));
	free(*get);
	*get = temp;
	return (1);
}

int		ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	if (!c)
		return (i);
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (i < start)
		return (ft_strjoin("", ""));
	sub = (char*)malloc(sizeof(char) *
		((i - start < len) ? i - start : len) + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, ((i - start < len) ? i - start : len) + 1);
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	l1 = ft_strchr(s1, '\0');
	l2 = ft_strchr(s2, '\0');
	res = (char*)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!res)
		return (NULL);
	res[l1 + l2] = '\0';
	i = 0;
	while (i < l1 || i < l2)
	{
		if (i < l1)
			res[i] = s1[i];
		if (i < l2)
			res[i + l1] = s2[i];
		i++;
	}
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char			*get;
	char				*tmp;
	char				hold[BUFFER_SIZE + 1];
	int					readl;

	if (!get)
	{
		get = (char*)malloc(sizeof(char));
		get[0] = '\0';
	}
	if (read(fd, 0, 0) == -1)
		return (-1);
	readl = 1;
	while (readl && !ft_strchr(get, '\n'))
	{
		readl = read(fd, hold, BUFFER_SIZE);
		hold[readl] = 0;
		tmp = ft_strjoin(get, hold);
		free(get);
		get = tmp;
	}
	if (readl)
		return (pull_line(&get, line, '\n'));
	else
		return (pull_line(&get, line, '\0'));
}
