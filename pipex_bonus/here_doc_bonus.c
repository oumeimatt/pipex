/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 13:59:49 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/01 17:13:14 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_tokens	*hd_tokens(char **argv)
{
	t_tokens *tokens;
	char	**cmd1;
	char	**cmd2;

	tokens = NULL;
	cmd1 = ft_split(argv[3], ' ');
	cmd2 = ft_split(argv[4], ' ');
	ft_add_node(&tokens, cmd1);
	ft_add_node(&tokens, cmd2);
	return (tokens);
}

void	read_line(t_tokens *tokens, char **split_path, char **argv)
{
	char	*line;
	char	*limiter;
	int		fd;

	fd = open("/tmp/helper", O_RDONLY | O_WRONLY | O_CREAT, 0644);
	limiter = argv[2];
	while (get_next_line(0, &line) > 0)
	{
		if (strcmp(line, limiter) == 0)
			break;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	if (strcmp(argv[3], "") != 0)
		tokens->cmd[0] = absolute_path(tokens->cmd[0], split_path);
	if (strcmp(argv[4], "") != 0)
		tokens->next->cmd[0] = absolute_path(tokens->next->cmd[0], split_path);
}

void	exec_cmd1(char **argv, char **cmd, t_tokens *tokens)
{
	char	**split_arg;
	int		in;

	in = open("/tmp/helper", O_RDONLY);
	close(tokens->in);
	dup2(tokens->out, 1);
	dup2(in, 0);
	unlink("/tmp/helper");
	if (strcmp(argv[3], "") == 0)
	{
		ft_putstr_fd(" : command not found\n", 2);
		exit(0);
	}
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		split_arg = ft_split(argv[3], ' ');
		ft_putstr_fd("pipex1: command not found: ", 2);
		ft_putendl_fd(split_arg[0], 2);
		exit(0);
	}
}

void	exec_cmd2(char **argv, char **cmd, t_tokens *tokens)
{
	int		out;
	char	**split_arg;

	out = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		perror(argv[5] );
		exit(1);
	}
	close(tokens->out);
	dup2(tokens->in, 0);
	dup2(out, 1);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		split_arg = ft_split(argv[4], ' ');
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(split_arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

int		here_doc(t_tokens *tokens, char **argv, char **split_path, int stats)
{
	int		pid[2];

	read_line(tokens, split_path, argv);
    
	ft_pipe(tokens);
	pid[0] = fork();
	if(pid[0] == -1)
		exit(EXIT_FAILURE);
	if(pid[0] == 0)
		exec_cmd1(argv, tokens->cmd, tokens);
	pid[1] = fork();
	if(pid[1] == -1)
		exit(EXIT_FAILURE);
	if(pid[1] == 0)
		exec_cmd2(argv, tokens->next->cmd, tokens);
	close (tokens->in);
	close(tokens->out);
	waitpid(pid[0], &stats, 0);
	waitpid(pid[1], &stats, 0);
	return (stats);
}