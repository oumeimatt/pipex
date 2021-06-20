/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:04:27 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/20 17:57:25 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_path(char **envp)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (envp[i] !=  NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == TRUE)
			line = ft_strdup(envp[i]);
		i++;
	}
	return (line);
}

	

	