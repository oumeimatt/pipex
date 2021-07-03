/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:20:39 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 14:30:50 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	empty_args(int argc, char **argv)
{
	int		i;
	int		out;

	i = 2;
	while (i < argc - 2)
	{
		if (strcmp(argv[i], "") == TRUE)
			ft_putstr_fd("pipex: :command not found\n", 2);
		i++;
	}
	if (strcmp(argv[argc - 2], "") == TRUE)
	{
		ft_putstr_fd("pipex: : command not found\n", 2);
		out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(out);
		exit(127);
	}
}

void	here_doc_args(int argc)
{
	if (argc != 6)
	{
		ft_putstr_fd("pipex : too much arguments \n", 2);
		exit(1);
	}
}

void	bonus_args(int argc, char **argv)
{
	if (strcmp(argv[1], "here_doc\0") == TRUE)
		here_doc_args(argc);
	else
	{
		if (argc < 5)
		{
			ft_putstr_fd("need more  arguments\n", 2);
			exit(1);
		}
		if (strcmp(argv[1], "") == TRUE)
		{
			ft_putstr_fd("pipex: : No such file or directory\n", 2);
			if (strcmp(argv[argc - 1], "") == TRUE)
			{
				ft_putstr_fd("pipex: : No such file or directory\n", 2);
				exit(1);
			}
		}
		empty_args(argc, argv);
	}
}
