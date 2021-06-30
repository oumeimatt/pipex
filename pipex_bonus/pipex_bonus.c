/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 10:15:46 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/30 12:14:25 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    ft_add_node(t_tokens **head_Ref, char **cmd)
{
	t_tokens    *new_node;
	t_tokens    *last;

	new_node = (t_tokens*) malloc(sizeof(t_tokens));
	last = *head_Ref;
	new_node->cmd = cmd;
	new_node->in = -1;
	new_node->out = -1;
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

void print_list(t_tokens *head) 
{
    t_tokens	*current_node = head;
   	while ( current_node != NULL)
	{
        printf("path ====== %s ", current_node->cmd[0]);
		printf("   %s\n ", current_node->cmd[1]);
        current_node = current_node->next;
	}
}

void	ft_pipe(t_tokens *tokens)
{
	int		fds[2];

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	// while (tokens != NULL && tokens->next != NULL)
	// {
		tokens->in = fds[0];
		tokens->out = fds[1];
		// tokens = tokens->next;
	// }
	tokens->next->in = tokens->in;
	tokens->out = tokens->out;
}

int     main(int argc, char ** argv, char **envp)
{
	t_tokens	*tokens;
	t_tokens	*tmp;
	char		*path;
	char		**split_path;
	pid_t		pid;
	int			i;
	// int			stats;
	int			pipes[2];

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
	else
	{
		tokens = init_tokens_2(argc, argv);
		tmp = tokens;
		while (tmp != NULL)
		{
			tmp->cmd[0] = absolute_path(tmp->cmd[0], split_path);
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
				break;
		}
		pipe(pipes);
		pid = fork();
		if (pid == 0)
			first_cmd(argv, tokens->cmd, pipes);
		dup2(pipes[0], 0);
		close(pipes[1]);
		tokens = tokens->next;
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
			dup2(pipes[0], 0);
			close(pipes[1]);
			i++;
			tokens = tokens->next;
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			last_cmd(argc, argv, tokens->cmd, pipes);
	}
}