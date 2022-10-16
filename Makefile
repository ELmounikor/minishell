# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:58:47 by mel-kora          #+#    #+#              #
#    Updated: 2022/10/16 16:49:19 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c\
			Libft/ft_putstrfd.c\
			Libft/ft_split.c\
			Libft/ft_strdup.c\
			Libft/ft_strjoin.c\
			Libft/ft_strlen.c\
			Libft/ft_strtrim.c\
			Libft/ft_strncmp.c\
			Libft/ft_strnstr.c\
			Libft/ft_strchr.c\
			Libft/ft_atoi.c\
			Libft/get_next_line.c\
			Libft/ft_isnum.c\
			Libft/ft_lstnew.c\
			Libft/ft_lstiter.c\
			Libft/ft_lstclear.c\
			Libft/ft_lstadd_back.c\
			Libft/ft_lstadd_front.c\
			Libft/ft_lstdelone.c\
			Libft/ft_lstlast.c\
			Libft/ft_lstsize.c\
			Libft/ft_substr.c\
			Libft/ft_isalnum_.c\
			Libft/ft_isspace.c\
			Libft/ft_strcmp.c\
			Libft/ft_itoa.c\
			Parsing/lexer.c\
			Parsing/expander.c\
			Parsing/syntax_checker.c\
			Parsing/extractor.c\
			Parsing/file_handler.c\
			Builtins/history.c\
			Builtins/unset.c\
			Builtins/add_env.c\
			Builtins/cd.c\
			Builtins/echo.c\
			Builtins/env.c\
			Builtins/export.c\
			Builtins/pwd.c\
			Builtins/list_env.c\
			Builtins/ft_builtins.c\
			Builtins/ft_split_env.c\
			Builtins/ft_atoi_exit.c\
			Builtins/exit.c\
			execution/ft_pipe.c\
			execution/ft_get_path.c\
			execution/ft_outils_pipe.c\
			execution/ft_signal.c
			#Builtins/ft_pipex/childs.c\
			#Builtins/ft_pipex/ft_utils_list.c\
			#Builtins/ft_pipex/get_cmd_path.c\
			#Builtins/ft_pipex/pipex.c\
			#Builtins/ft_pipex/pipex_bonus.c\
			#Builtins/ft_pipex/pipex_bonuso.c\

OBJS	=	${SRCS:.c=.o}
NAME	=	minishell
CC		=	@gcc
RM		=	@rm -rf
LIB		=   -L ~/goinfre/.brew/opt/readline/lib
INC		=	-I ~/goinfre/.brew/opt/readline/include
CFLAGS	=	-Wall -Werror -Wextra #-g -fsanitize=address

all:		${NAME}
			@echo "\033[0;93m	<< all done by S&M! >>"

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline ${LIB} ${INC}
			@echo "\033[1;92m	--------->>> files created :D"
			@echo "\033[0;93m	        (        )  (    (        )       (     (     "
			@echo "\033[0;93m	 (      )\ )  ( /(  )\ ) )\ )  ( /(       )\ )  )\ )  "
			@echo "\033[0;93m	 )\))(  (()/(  )\())(()/((()/(  )\()) (   (()/( (()/(  "
			@echo "\033[1;93m	((_)()\  /(_))((_)\  /(_))/(_))((_)\  )\   /(_)) /(_)) "
			@echo "\033[1;93m	(_()((_)(_))   _((_)(_)) (_))   _((_)((_) (_))  (_))   "
			@echo "\033[1;33m	|  \/  ||_ _| | \| ||_ _|/ __| | || || __|| |   | |    "
			@echo "\033[1;33m	| |\/| | | |  | .  | | | \__ \ | __ || _| | |__ | |__  "
			@echo "\033[1;33m	|_|  |_||___| |_|\_||___||___/ |_||_||___||____||____| "

clean:
			${RM} ${OBJS}
			@echo "\033[1;91m	--------->>> files deleted :}"

fclean:		clean
			${RM} ${NAME} Libft/.sh_history
		
re:			fclean all

.PHONY:		all clean fclean re