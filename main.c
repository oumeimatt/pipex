/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:10 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/20 17:57:21 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

t_tokens    *init_tokens(int argc, char **argv)
{
	int			i;
	t_tokens	*tokens;
	char		**cmd1;
	char		**cmd2;

	cmd1 = ft_split(argv[2], ' ');
	ft_add_node(&tokens, cmd1);
	cmd2 = ft_split(argv[3], ' ');
	ft_add_node(&tokens, cmd2);
	return (tokens);
}
int main(int argc, char **argv, char **envp)
{
	int         fds[2];
	pid_t       pid;
	t_tokens    *tokens;
	int         in;
	char		*path;
	char		**split_path;
	int			acc;
	
	if(argc != 5)
	{
		ft_putstr_fd("Error : need 5 arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	in = open(argv[1], O_RDONLY);
	if (in == -1)
	{
		perror(argv[1] );
		exit(EXIT_FAILURE);
	}
	tokens = init_tokens(argc, argv);
	path = get_path(envp);
	split_path = ft_split(path, ':');
	int i = 1;
	char *first;
	first = split_path[0] + 5;
	char *tmp = ft_strjoin(first, "/");
	char *tmp2 = ft_strjoin(tmp, tokens->cmd[0]);
	acc = access(tmp2, F_OK);
	while (acc != 0 && split_path[i] != NULL)
	{
		free(tmp);
		free(tmp2);
		tmp = ft_strjoin(split_path[i], "/");
		tmp2 = ft_strjoin(tmp, tokens->cmd[0]);
		printf("tmp2 == %s\n", tmp2);
		acc = access(tmp2, F_OK);
		i++;
	}
	if (acc == 0)
		tokens->cmd[0] = tmp2;
	printf("first cmd ===== %s\n", tokens->cmd[0]);
	if(pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		execve(tokens->cmd[0], tokens->cmd, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		close(fds[1]);
	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	if(pid == 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		execve(tokens->next->cmd[0], tokens->next->cmd, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		close(fds[0]);
}