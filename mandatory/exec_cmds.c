/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:18:54 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 14:10:38 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_first_cmd(char **argv, t_all *all, int fds[2])
{
	int		in;
	char	**split_arg;

	in = open(argv[1], O_RDONLY);
	if (in == -1)
	{
		perror(argv[1]);
		exit(0);
	}
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(in, 0);
	if (execve(all->cmd1_path, all->cmd1, NULL) == -1)
	{
		if (strcmp(argv[2], ""))
		{
			split_arg = ft_split(argv[2], ' ');
			ft_putstr_fd("pipex3: command not found: ", 2);
			ft_putendl_fd(split_arg[0], 2);
			free_strtab(split_arg);
		}
		exit(0);
	}
	free_strtab(all->cmd1);
	free(all->cmd1_path);
}

void	exec_sec_cmd(char **argv, t_all *all, int fds[2])
{
	int		out;
	char	**split_arg;

	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(argv[4]);
		exit(1);
	}
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	if (execve(all->cmd2_path, all->cmd2, NULL) == -1)
	{
		split_arg = ft_split(argv[3], ' ');
		ft_putstr_fd("pipex4: command not found: ", 2);
		ft_putendl_fd(split_arg[0], 2);
		free_strtab(split_arg);
		exit(127);
	}
	free_strtab(all->cmd2);
	free(all->cmd2_path);
	all->cmd2_path = NULL;
}
