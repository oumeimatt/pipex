/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:10 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/30 13:16:43 by oel-yous         ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	int         fds[2];
	pid_t       pid;
	char		**cmd1;
	char		**cmd2;
	char		*path;
	char		**split_path;
	int			stats;
	
	error_management(argc, argv);
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	path = get_path(envp);
	split_path = ft_split(path, ':');
	cmd1[0] = absolute_path(cmd1[0], split_path);
	cmd2[0] = absolute_path(cmd2[0], split_path);
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);	
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
		exec_first_cmd(argv, cmd1, fds);
	free_strtab(cmd1);
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
		exec_sec_cmd(argv, cmd2, fds);
	free_strtab(cmd2);
	free_strtab(split_path);
	close (fds[0]);
	close(fds[1]);
	while (wait(&stats) > 0)
	{
		printf("exit status = %d\n", WEXITSTATUS(stats));
 		// if (WIFEXITED(stats))
		//  	return (WEXITSTATUS(stats));
	}
	check_leaks();
}



