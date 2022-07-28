# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 16:48:53 by mel-kora          #+#    #+#              #
#    Updated: 2022/07/24 12:34:17 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_putstr_fd.c\
				ft_split.c\
				ft_strdup.c\
				ft_strjoin.c\
				ft_strlen.c\
				ft_strtrim.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_atoi.c\
				get_next_line.c\
				ft_isnum.c\

OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a

CC			=	gcc

RM			=	rm -rf

CFLAGS		=	-Wall -Werror -Wextra

.c.o:
		${CC} ${CFLAGS} -c $< -o $@
		ar -crs ${NAME} $@
			
all:		${NAME}

${NAME}:	${OBJS}

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re bonus
