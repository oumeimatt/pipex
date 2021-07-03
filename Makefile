# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 17:51:17 by oel-yous          #+#    #+#              #
#    Updated: 2021/07/03 14:40:28 by oel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address

SRCS		= 	mandatory/main.c

OBJS 		= $(SRCS:.c=.o)

BONUS_SRCS	=	pipex_bonus/pipex_bonus.c

BONUS_OBJS 	= $(BONUS:.c=.o)

all: $(SRCS)
		@make -C ./mandatory
		$(CC) $(CFLAGS) $(SRCS) ./mandatory/pipex.a -o $(NAME)

bonus: $(BONUS_SRCS)
		@make -C ./pipex_bonus
		$(CC) $(BONUS_SRCS) ./pipex_bonus/pipex_bonus.a $(CFLAGS) -o $(NAME)

clean:
		@rm -rf $(BONUS_OBJS) $(OBJS)
		@make -C ./mandatory clean
		@make -C ./pipex_bonus clean

fclean:clean
		@make -C ./mandatory fclean
		@make -C ./pipex_bonus fclean
		rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re