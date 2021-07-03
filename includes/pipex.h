/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:36 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 14:39:48 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TRUE 0
#define FALSE 1
#define BUFFER_SIZE 100000

typedef	struct s_all
{
	char	**cmd1;
	char	**cmd2;
	char	**split_p;
	char	*path;
	char	*cmd1_path;
	char	*cmd2_path;
	int		stats;
}				t_all;


typedef struct s_tokens
{
	char    **cmd;
	int     in;
	int     out;
	struct s_tokens *next;
}               t_tokens;

void	exec_first_cmd(char **argv, t_all *all, int fds[2]);
void	exec_sec_cmd(char **argv, t_all *all, int fds[2]);
size_t	ft_numwords(char const *s, char c);
char	**ft_free(char **str, int num);
char	**ft_split(char const *s, char c);
char	*get_path(char **envp);
char	*free_ret(char *str1, char *str2, char *to_ret);
int	check_first(char **s_path, char *cmd);//
char	*absolute_path(char *cmd, char **s_path); //
void	error_management(int argc, char **argv);
void	free_strtab(char **tab);
t_all	*init_all(char **argv, char **envp);
void	free_all(t_all *all);
void	exec_command(t_all *all, char **argv);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);








#endif