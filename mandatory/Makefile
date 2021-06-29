# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 15:22:29 by oel-yous          #+#    #+#              #
#    Updated: 2021/06/29 15:53:41 by oel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

SRCS		=  exec_cmds.c \
				ft_split.c \
				get_path.c \
				utils.c \
				tools.c \

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