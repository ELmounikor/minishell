# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 16:48:53 by mel-kora          #+#    #+#              #
#    Updated: 2022/10/16 10:37:14 by mel-kora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	unset.c\
			add_env.c\
			cd.c\
			echo.c\
			env.c\
			export.c\
			pwd.c\
			list_env.c\
			ft_builtins.c\
			ft_split_env.c\
			ft_atoi_exit.c\
			exit.c\
			ft_builtins.c\
			../execution/ft_pipe.c\
			../execution/ft_get_path.c\
			../execution/ft_outils_pipe.c\
			#../execution/ft_signal.c
			#ft_pipex/childs.c\
			#ft_pipex/ft_utils_list.c\
			#ft_pipex/get_cmd_path.c\
			#ft_pipex/pipex.c\
			#ft_pipex/pipex_bonus.c\
			#ft_pipex/pipex_bonuso.c\

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
