# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 17:51:17 by oel-yous          #+#    #+#              #
#    Updated: 2021/07/03 17:36:24 by oel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror 

SRCS		= 	mandatory/main.c

OBJS 		= $(SRCS:.c=.o)

BONUS_SRCS	=	pipex_bonus/pipex_bonus.c

BONUS_OBJS 	= $(BONUS:.c=.o)

all: $(NAME)

$(NAME):$(SRCS)
	@make -C ./mandatory
	$(CC) $(CFLAGS) $(SRCS) ./mandatory/pipex.a -o $(NAME)

bonus: $(BONUS_SRCS)
		@make -C ./pipex_bonus
		$(CC) $(BONUS_SRCS) ./pipex_bonus/pipex_bonus.a $(CFLAGS) -o pipex

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