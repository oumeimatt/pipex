/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:04:27 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/22 19:59:34 by oel-yous         ###   ########.fr       */
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

char	*absolute_path(char *path, char *cmd, char **s_path)
{
	int		i;
	char	*first;
	char	*tmp;
	char	*commande;
	int		acc;

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
		cmd = commande;
	else
		cmd = NULL;
	return (cmd);
}

void	error_management(int argc, char **argv)
{
	int		in;
	int		out;
	char	*path;

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
		exit(EXIT_FAILURE);
	}
	in = access(argv[1], F_OK | R_OK);
	out = open(argv[4], O_WRONLY | O_CREAT);
	if (in != 0)
	{
		perror(argv[1] );
		exit(EXIT_FAILURE);
	}
	if (out == -1)
	{
		perror(argv[4] );
		exit(EXIT_FAILURE);
	}
}
void	cmd_not_found(char **argv, char *cmd1, char *cmd2)
{
	char	**split_arg;

	if (cmd1 == NULL)
	{
		split_arg = ft_split(argv[2], ' ');
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_arg[0], 2);
	}
	if (cmd2 == NULL)
	{
		split_arg = ft_split(argv[3], ' ');
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_arg[0], 2);
	}
}