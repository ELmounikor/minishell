# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 16:48:53 by mel-kora          #+#    #+#              #
#    Updated: 2022/09/19 21:28:14 by mounikor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	history.c\


OBJS	=	${SRCS:.c=.o}

NAME	=	builtins.a

CC		=	@gcc

RM		=	@rm -rf

CFLAGS	=	-Wall -Werror -Wextra

.c.o:
			${CC} ${CFLAGS} -c $< -o $@
			@ar -crs ${NAME} $@
			
all:		${NAME}

${NAME}:	${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
