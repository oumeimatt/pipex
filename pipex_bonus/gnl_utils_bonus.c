/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:35:55 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/29 15:41:03 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			ch;
	unsigned char	*str;

	i = 0;
	ch = (char)c;
	str = (unsigned char *)s;
	while (*str)
	{
		if (*str == ch)
			return ((char *)(str + i));
		str++;
	}
	if (ch == '\0')
		return ((char*)str);
	return (NULL);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL || !s1 || !s2)
		return (NULL);
	i = 0;
	j = ft_strlen((char*)s1);
	while (i < j)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	newstr = (char*)malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (len-- > 0)
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
