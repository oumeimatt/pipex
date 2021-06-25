/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 04:18:37 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/25 13:00:24 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_word(char const *str, int i, int *nb_word, int c)
{
	*nb_word += 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

void	ft_free2(char **tab, int n)
{
	int	i;

	i = 0;
	while (i > n)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

int		ft_add_word(char **tab, char const *str, int *nb_word, int c)
{
	int		word_len;
	int		j;
	char	*tmp;
	int		k;

	word_len = 0;
	k = 0;
	while (str[word_len] != c && str[word_len] != '\0')
		word_len++;
	if (!(tmp = (char *)malloc((word_len + 1) * sizeof(char))))
	{
		ft_free2(tab, *nb_word);
		*nb_word = 0;
		return (strlen(str));
	}
	tmp[word_len] = '\0';
	j = 0;
	while (k < word_len)
	{
		tmp[j] = str[k++];
		j++;
	}
	tab[*nb_word] = tmp;
	*nb_word += 1;
	return (word_len);
}

void	initial(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char			**ft_split(char const *str, char c)
{
	int		i;
	char	**tab;
	int		number_words;

	initial(&i, &number_words);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
		if (str[i] != c)
			i = ft_word(str, i, &number_words, c);
		else
			i++;
	if (!(tab = (char **)malloc((number_words + 1) * sizeof(char *))))
		return (NULL);
	tab[number_words] = 0;
	initial(&i, &number_words);
	while (str[i] != '\0')
		if (str[i] != c)
			i += ft_add_word(tab, str + i, &number_words, c);
		else
			i++;
	if (!number_words && !tab)
		return (NULL);
	return (tab);
}
