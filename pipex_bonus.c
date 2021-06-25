/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 10:15:46 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/25 18:27:54 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// i need to fix cmd1 ="" ||  cmm2 = ""



void    ft_add_node(t_tokens **head_Ref, char **cmd)
{
	t_tokens    *new_node;
	t_tokens    *last;

	new_node = (t_tokens*) malloc(sizeof(t_tokens));
	last = *head_Ref;
	new_node->cmd = cmd;
	new_node->next = NULL;
	if (*head_Ref == NULL)
	{
		*head_Ref = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}

void    bonus_args(int argc, char **argv)
{
	int     i;

	if (strcmp(argv[1], "here_doc\0") == TRUE)
	{
		if (argc != 6)
		{
			ft_putstr_fd("too much arguments \n", 2);
			exit(1);
		}
	}
	else
	{
		if (argc < 5)
		{
			ft_putstr_fd("need more  arguments\n", 2);
			exit(1);
		}
		i = 2;
		while (i < argc - 2)
		{
			if (strcmp(argv[i], "") == TRUE)
				ft_putstr_fd(" : command not found\n", 2);
			i++;
		}
		if (strcmp(argv[argc - 2], "") == TRUE)
		{
			ft_putstr_fd(" : command not found\n", 2);
			exit(127);
		}
	}
}

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
		tokens->cmd[0] = tokens->cmd[0] = absolute_path(tokens->cmd[0], split_path);
	if (strcmp(argv[4], "") != 0)
		tokens->next->cmd[0] = absolute_path(tokens->next->cmd[0], split_path);
}

void print_list(t_tokens *head) 
{
    t_tokens	*current_node = head;
   	while ( current_node != NULL)
	{
        printf("list ====== %s ", current_node->cmd[0]);
		printf("   %s\n ", current_node->cmd[1]);
        current_node = current_node->next;
	}
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
		ft_putstr_fd("pipex: command not found: ", 2);
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
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_arg[0], 2);
		exit(127);
	}
}

void	ft_pipe(t_tokens *tokens)
{
	int		fds[2];

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);	
	tokens->in = fds[0];
	tokens->out = fds[1];
}

int		here_doc(t_tokens *tokens, char **argv, char **split_path)
{
	int		stats;
	int		pid;

	read_line(tokens, split_path, argv);
	ft_pipe(tokens);
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
		exec_cmd1(argv, tokens->cmd, tokens);
	while (wait(&stats) > 0);
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
		exec_cmd2(argv, tokens->next->cmd, tokens);
	close (tokens->in);
	close(tokens->out);
	while (wait(&stats) > 0)
	{
 		if (WIFEXITED(stats))
	 		return (WEXITSTATUS(stats));
	}
	return (0);
}
int     main(int argc, char ** argv, char **envp)
{
	t_tokens	*tokens;
	char		*path;
	char		**split_path;

	tokens = NULL;
	bonus_args(argc, argv);
	path = get_path(envp);
	split_path = ft_split(path, ':');
	if (strcmp(argv[1], "here_doc\0") == TRUE)
	{
		tokens = hd_tokens(argv);
		if (strcmp(argv[4], "") == TRUE)
		{
			read_line(tokens, split_path, argv);
			ft_putstr_fd(" : command not found\n", 2);
			exit(127);
		}
		return (here_doc(tokens, argv, split_path));
	}
}