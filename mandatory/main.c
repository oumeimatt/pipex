/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:10 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/29 17:51:09 by oel-yous         ###   ########.fr       */
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

t_tokens    *init_tokens(char **argv)
{
	t_tokens	*tokens;
	char		**cmd1;
	char		**cmd2;

	tokens = NULL;
	cmd1 = ft_split(argv[2], ' ');
	ft_add_node(&tokens, cmd1);
	cmd2 = ft_split(argv[3], ' ');
	ft_add_node(&tokens, cmd2);
	return (tokens);
}
int main(int argc, char **argv, char **envp)
{
	int         fds[2];
	pid_t       pids[2];
	t_tokens    *tokens;
	char		*path;
	char		**split_path;
	int			stats;
	
	error_management(argc, argv);
	tokens = init_tokens(argv);
	path = get_path(envp);
	split_path = ft_split(path, ':');
	tokens->cmd[0] = absolute_path(tokens->cmd[0], split_path);
	tokens->next->cmd[0] = absolute_path(tokens->next->cmd[0], split_path);
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);	
	pids[0] = fork();
	if(pids[0] == -1)
		exit(EXIT_FAILURE);
	if(pids[0] == 0)
		exec_first_cmd(argv, tokens->cmd, fds);
	pids[1] = fork();
	if(pids[1] == -1)
		exit(EXIT_FAILURE);
	if(pids[1] == 0)
		exec_sec_cmd(argv, tokens->next->cmd, fds);
	close (fds[0]);
	close(fds[1]);
	while (wait(&stats) > 0)
	{
		printf("exit status = %d\n", WEXITSTATUS(stats));
 		if (WIFEXITED(stats))
		 	return (WEXITSTATUS(stats));
	}
}



