NAME	= libftprintf.a
SRCS	= ${wildcard *.c}
OBJS	= ${SRCS:.c=.o}

CC		= gcc
FLAGS	= -Wall -Werror -Wextra
LIBC	= ar rc
RM		= rm -f

.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
			${LIBC} ${NAME} ${OBJS}

all:	${NAME}
bonus:	all

clean:
		${RM} ${OBJS}
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re bonus
