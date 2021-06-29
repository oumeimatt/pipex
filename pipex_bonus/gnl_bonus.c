/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 10:57:53 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/29 15:41:26 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int		ft_free(char **s1, int ret)
{
	free(*s1);
	*s1 = NULL;
	return (ret);
}

static int		ft_line(char **p, char **line, int ret)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	str = ft_strdup(*p);
	ft_free(p, 0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		*line = ft_substr(str, 0, i);
		temp = str;
		str = ft_strdup(&str[i + 1]);
		free(temp);
	}
	else
	{
		*line = ft_strdup(str);
		ft_free(&str, 0);
	}
	*p = str;
	if (ret == 0 && str == NULL)
		return (0);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char			*buf;
	char			*temp;
	int				ret;
	static char		*p[4864];

	if (BUFFER_SIZE < 0 || fd < 0 || !line || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (p[fd] == NULL)
		p[fd] = ft_strdup("");
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = p[fd];
		p[fd] = ft_strjoin(p[fd], buf);
		free(temp);
		if (ft_strchr(p[fd], '\n'))
			break ;
	}
	free(buf);
	if (ret < 0)
		return (ft_free(&p[fd], -1));
	else if (ret == 0 && p[fd] == NULL)
		return (ft_free(&p[fd], 0));
	return (ft_line(&p[fd], line, ret));
}
