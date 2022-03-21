SRCS		= 	${wildcard ./srcs/*.c} \
				${wildcard ./srcs/parsing/*.c} \
				${wildcard ./srcs/minimap/*.c} \
				${wildcard ./srcs/actions/*.c} \
				${wildcard ./srcs/world_3d/*.c} \
				${wildcard ./srcs/enemies/*.c} \

OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= cub3D
RM			= rm -f

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L./libft -lft

MINILIBX_DIR	= mlx
MINILIBX_A		= libmlx.a
MINILIBX		= -L./mlx -lmlx -framework OpenGL -framework AppKit

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR}/
			make --silent -C ${MINILIBX_DIR}/
			$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) ${OBJS} $(MINILIBX)

clean:
			${RM} ${OBJS}
# make --silent -C ${LIBFT_DIR} clean
# make --silent -C ${MINILIBX_DIR} clean

fclean:		clean
			${RM} ${NAME}
# make --silent -C ${LIBFT_DIR} fclean
# make --silent -C ${MINILIBX_DIR} clean

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run

#-------HELP TO DEBUG---------#

#-g -fsanitize=address ou -O0 à ajouter lors de la compliation pour le débegueur vscode.
#leaks -atExit -- ./commande (mac) qui permet de checker si il y'a des leaks.
#valgrind --leak-check=full --show-leak-kinds=all ./minishell
