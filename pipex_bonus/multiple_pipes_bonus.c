/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:57:24 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 13:35:46 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipes_loop(int argc, char **argv, t_tokens *tokens, int pipes[2])
{
	int		i;
	pid_t	pid;

	i = 3;
	while (i < argc - 2)
	{
		pipe(pipes);
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			dup2(pipes[1], 1);
			exec_cmd(argv, tokens->cmd, i);
		}
		dup2(pipes[0], 0);
		close(pipes[1]);
		i++;
		tokens = tokens->next;
	}
}

int	ft_help_mult(int argc, char **argv, t_tokens *tokens, int pipes[2])
{
	pid_t	pid;
	int		stats;

	stats = 0;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		last_cmd(argc, argv, tokens->cmd, pipes);
	while (waitpid(pid, &stats, 0) > 0)
		if (WIFEXITED(stats))
			return (WEXITSTATUS(stats));
	return (stats);
}

int	multiple_pipes(int argc, char **argv, t_tokens *tokens)
{
	int		pipes[2];
	pid_t	pid;
	int		count;
	int		i;
	int		stats;

	i = -1;
	count = count_list(tokens);
	stats = 0;
	pipe(pipes);
	pid = fork();
	if (pid == 0)
		first_cmd(argv, tokens->cmd, pipes);
	dup2(pipes[0], 0);
	close(pipes[1]);
	tokens = tokens->next;
	if (count != 2)
	{
		pipes_loop(argc, argv, tokens, pipes);
		while (++i < count - 2)
			tokens = tokens->next;
	}
	return (ft_help_mult(argc, argv, tokens, pipes));
}
