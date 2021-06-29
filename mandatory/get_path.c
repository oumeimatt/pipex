/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:04:27 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/29 15:22:16 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

char	*absolute_path(char *cmd, char **s_path)
{
	int		i;
	char	*first;
	char	*tmp;
	char	*commande;
	int		acc;
	char	*failed;

	failed = ft_strdup(cmd);
	if (cmd[0] == '/')
		return (cmd);
	i = 1;
	first = s_path[0] + 5;
	tmp = ft_strjoin(first, "/");
	commande = ft_strjoin(tmp, cmd);
	acc = access(commande, F_OK);
	while (acc != 0 && s_path[i] != NULL)
	{
		free(tmp);
		free(commande);
		tmp = ft_strjoin(s_path[i], "/");
		commande = ft_strjoin(tmp, cmd);
		acc = access(commande, F_OK);
		i++;
	}
	if (acc == 0)
	{
		cmd = commande;
		free(failed);
	}
	else
		cmd = failed;
	return (cmd);
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

