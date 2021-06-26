# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 17:51:17 by oel-yous          #+#    #+#              #
#    Updated: 2021/06/26 15:53:49 by oel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

SRCS		=  exec_cmds.c \
				ft_split.c \
				get_path.c \
				utils.c \
				bonus/get_next_line.c \
				bonus/get_next_line_utils.c \
				pipex_bonus.c \
				here_doc.c \
				multiple_pipes.c

OBJS 		= $(SRCS:.c=.o)

BONUS_OBJS 	= $(BONUS:.c=.o)

all: $(NAME)

$(NAME):$(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

bonus:	$(BONUS_NAME)

$(BONUS_NAME): $(BONUS)
				$(CC) $(BONUS) $(CFLAGS) -o $(BONUS_NAME)

clean:
		rm -rf $(OBJS) $(BONUS_OBJS)

fclean:clean
		rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re