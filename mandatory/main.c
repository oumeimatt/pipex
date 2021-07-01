/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:10 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/01 11:21:49 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_strtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
}

t_all	*init_all(char **argv, char **envp)
{
	t_all	*tmp;

	tmp = malloc(sizeof(t_all));
	tmp->cmd1 = NULL;
	tmp->cmd2 = NULL;
	tmp->path = NULL;
	tmp->split_p = NULL;
	tmp->cmd1_path = NULL;
	tmp->cmd2_path = NULL;
	tmp->cmd1 = ft_split(argv[2], ' ');
	tmp->cmd2 = ft_split(argv[3], ' ');
	tmp->path = get_path(envp);
	tmp->split_p = ft_split(tmp->path, ':');
	if (strcmp(argv[2], "") == 0)
		tmp->cmd1_path = NULL;
	else
		tmp->cmd1_path = absolute_path(tmp->cmd1[0], tmp->split_p);
	tmp->cmd2_path = absolute_path(tmp->cmd2[0], tmp->split_p);
	return (tmp);
}

void	free_all(t_all *all)
{
	free_strtab(all->split_p);
	free(all->cmd1_path);
	free(all->cmd2_path);
}

int	exec_command(t_all *all, char **argv)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_first_cmd(argv, all, fds);
	wait(&all->stats);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_sec_cmd(argv, all, fds);
	close (fds[0]);
	close(fds[1]);
	free_all(all);
	while (wait(&all->stats) > 0)
	{
		while (1);
		if (WIFEXITED(all->stats))
			return (WEXITSTATUS(all->stats));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_all		*all;

	error_management(argc, argv);
	all = init_all(argv, envp);
	return (exec_command(all, argv));
}
