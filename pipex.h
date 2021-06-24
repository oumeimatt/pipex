/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:36 by oel-yous          #+#    #+#             */
/*   Updated: 2021/06/24 16:48:14 by oel-yous         ###   ########.fr       */
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
typedef struct s_tokens
{
    char    **cmd;
    struct s_tokens *next;
}               t_tokens;


void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_isalpha(char c);
int		ft_isdigit(char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *str, char c);
static	void	initial(int *i, int *j);
static	int		ft_add_word(char **tab, char const *str, int *nb_word, int c);
static	void	ft_free(char **tab, int n);
static	int		ft_word(char const *str, int i, int *nb_word, int c);
char    *get_path(char **envp);
char	*absolute_path(char *path, char *cmd, char **s_path);
char	*ft_strjoin(char const *s1, char const *s2);
void	error_management(int argc, char **argv);
t_tokens    *init_tokens(int argc, char **argv);
void	ft_putendl_fd(char *s, int fd);
void	cmd_not_found(char **argv, char *cmd1, char *cmd2);
void	exec_first_cmd(char **argv, char **cmd, int fds[2]);
void	exec_sec_cmd(char **argv, char **cmd, int fds[2]);

#endif