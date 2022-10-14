# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:58:47 by mel-kora          #+#    #+#              #
#    Updated: 2022/10/14 20:58:23 by mel-kora         ###   ########.fr        #
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
LIB		=   -L ~/goinfre/.brew/opt/readline/lib
INC		=	-I ~/goinfre/.brew/opt/readline/include
CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address

all:		MKLibft MKBuiltins ${NAME}
			@echo "\033[0;93m	<< all done by S&M! >>"

Libft/%o : %c
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} Libft/libft.a Builtins/builtins.a ${OBJS} -o ${NAME} -lreadline ${LIB} ${INC}
			@echo "\033[1;92m	--------->>> files created :D"
			@echo "\033[0;93m	        (        )  (    (        )       (     (     "
			@echo "\033[0;93m	 (      )\ )  ( /(  )\ ) )\ )  ( /(       )\ )  )\ )  "
			@echo "\033[0;93m	 )\))(  (()/(  )\())(()/((()/(  )\()) (   (()/( (()/(  "
			@echo "\033[1;93m	((_)()\  /(_))((_)\  /(_))/(_))((_)\  )\   /(_)) /(_)) "
			@echo "\033[1;93m	(_()((_)(_))   _((_)(_)) (_))   _((_)((_) (_))  (_))   "
			@echo "\033[1;33m	|  \/  ||_ _| | \| ||_ _|/ __| | || || __|| |   | |    "
			@echo "\033[1;33m	| |\/| | | |  | .  | | | \__ \ | __ || _| | |__ | |__  "
			@echo "\033[1;33m	|_|  |_||___| |_|\_||___||___/ |_||_||___||____||____| "

MKLibft:
			@make -s -C Libft

MKBuiltins:
			@make -s -C Builtins

clean:
			${RM} ${OBJS}
			@make fclean -s -C Libft
			@make fclean -s -C Builtins
			@echo "\033[1;91m	--------->>> files deleted :}"

fclean:		clean
			${RM} ${NAME} Libft/.sh_history
		
re:			fclean all

.PHONY:		all clean fclean re MKLibft MKBuiltins