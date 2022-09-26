# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 14:18:36 by sennaama          #+#    #+#              #
#    Updated: 2022/09/26 22:27:17 by sennaama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_pipex/libft/ft_strlen.c ft_pipex/libft/ft_strnstr.c \
		ft_pipex/libft/ft_substr.c ft_pipex/libft/ft_strjoin.c\
		ft_pipex/libft/ft_strdup.c ft_pipex/libft/ft_split.c\
		ft_pipex/get_cmd_path.c ft_pipex/childs.c ft_pipex/ft_utils_list.c\
		builtins/cd.c builtins/echo.c builtins/ft_strncmp.c builtins/env.c\
		builtins/export.c builtins/ft_split_env.c builtins/add_env.c\
		builtins/unset.c builtins/main.c
OBJS	= ${SRCS:.c=.o}

EXEC	= minishell

CC 		= cc

CFLAGS	= -Wall -Werror -Wextra 

.c.o:
			${CC} ${CFLAGS} -c $< -o $@ 

${EXEC}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${EXEC}

all:		${EXEC}

clean:
			rm -rf ${OBJS}

fclean:		clean
			rm -rf ${EXEC}

re:			fclean all

.PHONY:		all clean fclean re 