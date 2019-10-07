/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvictor <dvictor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:37:03 by dvictor           #+#    #+#             */
/*   Updated: 2019/09/20 17:02:33 by dvictor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t		ft_strlenchr(char *str, char a)
{
	size_t	i;

	i = 0;
	while (str[i] != a && str[i] != '\0')
		i++;
	return (i);
}

static int			ft_checker(char **str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = *str;
	while (tmp[i] != '\n')
		if (!(tmp[i++]))
			return (0);
	return (1);
}

static char			*ft_strjoinfree(char *s1, char *s2, int fr_str)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (fr_str == 0)
		return (str);
	else if (fr_str == 1)
		free(s1);
	else if (fr_str == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (str);
}

static int			ft_first_start(int const fd, char **line, char **str)
{
	if (fd == -1 || MAX_FD > 2048 || BUFF_SIZE < 1
		|| !line || (!(str[fd]) && !(str[fd] = ft_strnew(0))))
		return (0);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*str[MAX_FD];
	char			*temp;
	char			buf[BUFF_SIZE + 1];
	size_t			reed;

	if ((read(fd, buf, 0) == -1) || !(ft_first_start(fd, line, str)))
		return (-1);
	while (!(ft_checker(&str[fd])) && (reed = read(fd, buf, BUFF_SIZE)))
	{
		buf[reed] = '\0';
		temp = str[fd];
		str[fd] = ft_strjoinfree(temp, buf, 1);
	}
	ft_bzero(buf, BUFF_SIZE);
	*line = ft_strsub(str[fd], 0, ft_strlenchr(str[fd], '\n'));
	if (*str[fd] != '\0')
	{
		if (ft_checker(&str[fd]))
			ft_strcpy(str[fd], ft_strchr(str[fd], '\n') + 1);
		else
			ft_strdel(&str[fd]);
		return (1);
	}
	return (0);
}
