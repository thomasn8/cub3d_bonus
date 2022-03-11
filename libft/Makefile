# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: desa <desa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 16:08:45 by adeslarz          #+#    #+#              #
#    Updated: 2022/03/03 11:08:10 by desa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_bzero.c		\
		ft_isascii.c	\
		ft_memcpy.c		\
		ft_strchr.c		\
		ft_tolower.c	\
		ft_isalnum.c	\
		ft_isdigit.c	\
		ft_memmove.c	\
		ft_strlen.c		\
		ft_toupper.c	\
		ft_atoi.c		\
		ft_isalpha.c	\
		ft_isprint.c	\
		ft_memset.c		\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_itoa.c		\
		ft_split.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		get_next_line.c	\
		ft_free_array.c	\
		ft_errors.c		\
		ft_notblank.c	\
		ft_charinstr.c	\
		ft_atol.c		\

NAME 		= libft.a

FLAGS 		= -Wall -Wextra -Werror

OBJS 		= ${SRCS:.c=.o}

AR 			= ar rc

RM 			= rm -f

all: 		${NAME}

${NAME}: 	${OBJS}
			${AR} ${NAME} ${OBJS}

%.o : %.c
			$(CC) -c $(FLAGS) $< -o $@

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re