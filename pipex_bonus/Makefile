# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 15:22:32 by oel-yous          #+#    #+#              #
#    Updated: 2021/07/03 16:40:34 by oel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex_bonus.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

SRCS		=  ft_split_bonus.c \
				gnl_bonus.c \
				utils_2_bonus.c \
				gnl_utils_bonus.c \
				multiple_pipes_bonus.c \
				exec_all_cmds_bonus.c \
				here_doc_bonus.c \
				get_path_bonus.c \
				utils_bonus.c \
				check_args_bonus.c

OBJS 		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(SRCS)
		@$(CC) $(CFLAGS) -c $(SRCS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)

clean:
		rm -rf $(OBJS)

fclean:clean
		rm -rf $(NAME)

re: fclean all