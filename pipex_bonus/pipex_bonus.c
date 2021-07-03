/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 10:15:46 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 13:16:04 by oel-yous         ###   ########.fr       */
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

void	ft_pipe(t_tokens *tokens)
{
	int		fds[2];

	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	while (tokens != NULL && tokens->next != NULL)
	{
		tokens->in = fds[0];
		tokens->out = fds[1];
		tokens = tokens->next;
	}
}

int     main(int argc, char ** argv, char **envp)
{
	t_tokens	*tokens;
	char		*path;
	int			stats;;
	char		**split_path;

	stats = 0;
	tokens = NULL;
	bonus_args(argc, argv);
	path = get_path(envp);
	split_path = ft_split(path, ':');
	if (strcmp(argv[1], "here_doc\0") == TRUE)
	{
		tokens = hd_tokens(argv);
		stats = ft_here_doc(argv, tokens, split_path, stats);
	}
	else
	{
		tokens = init_tokens_2(argc, argv);
		stats = ft_mult_pipes(argc, argv, tokens, split_path);
	}
	system("leaks pipex");
	return(stats);
}

int		ft_here_doc(char **argv, t_tokens *tokens, char **split_path, int stats)
{
	if (strcmp(argv[4], "") == TRUE || strcmp(argv[3], "") == TRUE)
	{
		read_line(tokens, split_path, argv);
		if (strcmp(argv[3], "") == TRUE)
			ft_putstr_fd("pipex : command not found\n", 2);
		if (strcmp(argv[4], "") == TRUE)
			ft_putstr_fd("pipex : command not found\n", 2);
		exit(127);
	}
	return (here_doc(tokens, argv, split_path, stats));
}

int	ft_mult_pipes(int argc, char **argv, t_tokens *tokens, char **split_path)
{
	int			i;
	t_tokens	*tmp;

	i = 2;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (strcmp(argv[i], "") == 0)
		{
			tmp->cmd[0] = NULL;
			i++;
		}
		else
			tmp->cmd[0] = absolute_path(tmp->cmd[0], split_path);
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
	return (multiple_pipes(argc, argv , tokens));
}