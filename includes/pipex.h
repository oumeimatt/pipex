/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:32:36 by oel-yous          #+#    #+#             */
/*   Updated: 2021/07/03 17:14:40 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define TRUE 0
# define FALSE 1
# define BUFFER_SIZE 100000

typedef struct s_all
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
	char			**cmd;
	int				in;
	int				out;
	struct s_tokens	*next;
}				t_tokens;

void		exec_first_cmd(char **argv, t_all *all, int fds[2]);
void		exec_sec_cmd(char **argv, t_all *all, int fds[2]);
int			ft_word(char const *str, int i, int *nb_word, int c);
int			ft_add_word(char **tab, char const *str, int *nb_word, int c);
void		initial(int *i, int *j);
char		**ft_return(char **tab, int number_words);
char		**ft_split(char const *str, char c);
char		*get_path(char **envp);
char		*free_ret(char *str1, char *str2, char *to_ret);
int			check_first(char **s_path, char *cmd);//
char		*absolute_path(char *cmd, char **s_path); //
void		error_management(int argc, char **argv);
void		free_strtab(char **tab);
t_all		*init_all(char **argv, char **envp);
void		free_all(t_all *all);
void		exec_command(t_all *all, char **argv);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putendl_fd(char *s, int fd);

void		empty_args(int argc, char **argv);
void		here_doc_args(int argc);
void		bonus_args(int argc, char **argv);
t_tokens	*init_tokens_2(int argc, char	**argv);
void		first_cmd(char **argv, char **cmd, int pipes[2]);
void		exec_cmd(char **argv, char **cmd, int i);
void		last_cmd(int argc, char **argv, char **cmd, int pipes[2]);
int			ft_finish(char **str, char **line);
int			ft_remplissage(char **str, char **line, int len);
int			ft_read(int fd, char **str);
int			get_next_line(int fd, char **line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
t_tokens	*hd_tokens(char **argv);
void		read_line(t_tokens *tokens, char **split_path, char **argv);
void		exec_cmd1(char **argv, char **cmd, t_tokens *tokens);
void		exec_cmd2(char **argv, char **cmd, t_tokens *tokens);
int			here_doc(t_tokens *tokens, char **argv,
				char **split_path, int stats);
void		pipes_loop(int argc, char **argv, t_tokens *tokens, int pipes[2]);
int			ft_help_mult(int argc, char **argv, t_tokens *tokens, int pipes[2]);
int			multiple_pipes(int argc, char **argv, t_tokens *tokens);
void		ft_add_node(t_tokens **head_Ref, char **cmd);
void		ft_pipe(t_tokens *tokens);
int			ft_here_doc(char **argv, t_tokens *tokens,
				char **split_path, int stats);
int			ft_mult_pipes(int argc, char **argv,
				t_tokens *tokens, char **split_path);
int			count_list(t_tokens *head);
int			ft_strcmp(char *s1, char *s2);

#endif
