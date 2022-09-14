# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:58:47 by mel-kora          #+#    #+#              #
#    Updated: 2022/09/14 13:12:24 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c\
			lexer.c\
			syntax_checker.c\
			expander.c\
			Builtins/history.c\
			
OBJS	=	${SRCS:.c=.o}
NAME	=	minishell
CC		=	@gcc
RM		=	@rm -rf
LIB		=	-L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/editline
RDINC	=	-I /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/editline/readline.h
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g

all:		${NAME} 
			
${NAME}:	${OBJS}
			@make -C Libft
			${CC} ${CFLAGS} Libft/libft.a ${OBJS} -o ${NAME} -lreadline $(LIB) $(RDINC)
			@echo "\033[1;92m	--------->>> files created :D"
			@echo "\033[1;93m	        (        )  (    (        )       (     (     "
			@echo "\033[1;93m	 (      )\ )  ( /(  )\ ) )\ )  ( /(       )\ )  )\ )  "
			@echo "\033[1;93m	 )\))(  (()/(  )\())(()/((()/(  )\()) (   (()/( (()/(  "
			@echo "\033[1;93m	((_)()\  /(_))((_)\  /(_))/(_))((_)\  )\   /(_)) /(_)) "
			@echo "\033[1;93m	(_()((_)(_))   _((_)(_)) (_))   _((_)((_) (_))  (_))   "
			@echo "\033[1;33m	|  \/  ||_ _| | \| ||_ _|/ __| | || || __|| |   | |    "
			@echo "\033[1;33m	| |\/| | | |  | .  | | | \__ \ | __ || _| | |__ | |__  "
			@echo "\033[1;33m	|_|  |_||___| |_|\_||___||___/ |_||_||___||____||____| "
			
clean:
			${RM} ${OBJS} ${OBJS_BONUS}
			@make fclean -C Libft
			@echo "\033[1;91m	--------->>> files deleted :}"

fclean:		clean
			${RM} ${NAME} Libft/.sh_history
		
re:			fclean all

.PHONY:		all clean fclean re