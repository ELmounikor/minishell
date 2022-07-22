# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:58:47 by mel-kora          #+#    #+#              #
#    Updated: 2022/07/22 19:51:04 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c\
				history.c\

OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

CC			=	gcc

RM			=	rm -rf

CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -g

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME} 
			
${NAME}:	${OBJS}
			cd Libft; make; cd ..
			${CC} ${CFLAGS} Libft/libft.a ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			cd Libft; make fclean; cd ..

fclean:		clean
			${RM} ${NAME}
		
re:			fclean all

.PHONY:		all clean fclean re