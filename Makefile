# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:58:47 by mel-kora          #+#    #+#              #
#    Updated: 2022/09/26 21:59:12 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c\
			lexer.c\
			expander.c\
			syntax_checker.c\
			extractor.c\
			file_handler.c\
			path_finder.c\

OBJS	=	$(addprefix Libft/, ${SRCS:.c=.o})
NAME	=	minishell
CC		=	@gcc
RM		=	@rm -rf
LIB		=	-L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/editline
RDINC	=	-I /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/editline/readline.h
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=address -g

all:		${NAME} 

Libft/%o : %c
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${OBJS}
			@make -C Libft
			@make -C Builtins
			${CC} ${CFLAGS} Libft/libft.a Builtins/builtins.a ${OBJS} -o ${NAME} -lreadline $(LIB) $(RDINC)
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
			${RM} ${OBJS}
			@make fclean -C Libft
			@make fclean -C Builtins
			@echo "\033[1;91m	--------->>> files deleted :}"

fclean:		clean
			${RM} ${NAME} Libft/.sh_history
		
re:			fclean all

.PHONY:		all clean fclean re