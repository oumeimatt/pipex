/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmds_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:17:52 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/05 10:43:01 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_tokens	*init_tokens_2(int argc, char	**argv)
{
	t_tokens	*tokens;
	char		**cmd;
	int			i;

	i = 2;
	tokens = NULL;
	while (i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		ft_add_node(&tokens, cmd);
		i++;
	}
	return (tokens);
}

void	first_cmd(char **argv, char **cmd, int pipes[2])
{
	int		in;
	char	**split_arg;

	in = open(argv[1], O_RDONLY);
	if (in == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		exit(1);
	}
	dup2(pipes[1], 1);
	dup2(in, 0);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		if (ft_strcmp(argv[2], ""))
		{
			split_arg = ft_split(argv[2], ' ');
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(split_arg[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(0);
	}
}

void	exec_cmd(char **argv, char **cmd, int i)
{
	char	**split_arg;

	if (execve(cmd[0], cmd, NULL) == -1)
	{
		if (ft_strcmp(argv[i], ""))
		{
			split_arg = ft_split(argv[i], ' ');
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(split_arg[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(0);
	}
}

void	last_cmd(int argc, char **argv, char **cmd, int pipes[2])
{
	int		out;
	char	**split_arg;

	out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		perror(argv[argc - 1]);
		exit(1);
	}
	dup2(pipes[0], 0);
	dup2(out, 1);
	if (execve(cmd[0], cmd, NULL) == -1)
	{
		split_arg = ft_split(argv[argc - 2], ' ');
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(split_arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}
