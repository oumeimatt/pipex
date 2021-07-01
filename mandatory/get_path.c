/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:04:27 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/01 11:20:00 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char **envp)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == TRUE)
			line = envp[i];
		i++;
	}
	return (line);
}

char	*free_ret(char *str1, char *str2, char *to_ret)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	return (to_ret);
}

int	check_first(char **s_path, char *cmd)
{
	char	*first;
	int		acc;
	char	*tmp;
	char	*commande;

	first = s_path[0] + 5;
	tmp = ft_strjoin(first, "/");
	commande = ft_strjoin(tmp, cmd);
	acc = access(commande, F_OK);
	if (acc != 0)
	{
		free(tmp);
		free(commande);
	}
	return (acc);
}

char	*absolute_path(char *cmd, char **s_path)
{
	int		i;
	char	*tmp;
	char	*commande;
	int		acc;
	char	*failed;

	if (cmd[0] == '/')
		return (cmd);
	failed = ft_strdup(cmd);
	i = 0;
	acc = check_first(s_path, cmd);
	while (acc != 0 && s_path[++i] != NULL)
	{
		tmp = ft_strjoin(s_path[i], "/");
		commande = ft_strjoin(tmp, cmd);
		acc = access(commande, F_OK);
		if (acc != 0 && s_path[i + 1] != NULL)
			free(commande);
		free(tmp);
	}
	if (acc == 0)
		return (free_ret(cmd, failed, commande));
	else
		return (free_ret(cmd, commande, failed));
}

void	error_management(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error : need 5 arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[2], "") == TRUE)
		ft_putstr_fd(" : command not found\n", 2);
	if (strcmp(argv[3], "") == TRUE)
	{
		ft_putstr_fd(" : command not found\n", 2);
		exit(127);
	}
}
