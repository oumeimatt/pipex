/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:57:24 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/01 16:12:51 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int    pipes_loop(int argc,char **argv, t_tokens *tokens, int pipes[2])
{
	int     i;
	pid_t   pid;
	int		stats;

	i = 3;
	while (i < argc - 2)
	{
		pipe(pipes);
		pid =  fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			dup2(pipes[1], 1);
			exec_cmd(argv, tokens->cmd, i);
		}
		while (wait(&stats) > 0)
		dup2(pipes[0], 0);
		close(pipes[1]);
		i++;
		tokens = tokens->next;
	}
	return (stats);
}

int	multiple_pipes(int argc, char **argv, t_tokens *tokens)
{
	int		stats;
	int		pipes[2];
	pid_t	pid;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
		first_cmd(argv, tokens->cmd, pipes);
	while(wait(&stats) > 0);
	dup2(pipes[0], 0);
	close(pipes[1]);
	tokens = tokens->next;
	stats = pipes_loop(argc, argv, tokens, pipes);
	tokens = tokens->next;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		last_cmd(argc, argv, tokens->cmd, pipes);
	while (wait(&stats) > 0)
	{
		// while (1)
		// {};
 		if (WIFEXITED(stats))
	 		return (WEXITSTATUS(stats));
	}
	return (0);
}