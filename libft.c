/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:24:12 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/22 19:25:00 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int		ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (TRUE);
	return (FALSE);
}

int		ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (TRUE);
	return (FALSE);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		length;
	char	*temp;

	length = 0;
	while (s1[length] != '\0')
		length++;
	if (!s1)
		return (NULL);
	temp = (char*)malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		temp[i] = (char)s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] == (unsigned char)s2[i])
	{
		if (s1[i] == '\0' || i >= (n - 1))
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!s1 && s2)
		return ((char*)s1);
	if (s1 && !s2)
		return ((char*)s2);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char*)s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[len] = '\0';
	return (str);
}

void	ft_putendl_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
