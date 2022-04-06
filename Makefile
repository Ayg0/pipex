CC = cc

NAME = pipex

B_NAME = bonus/pipex

CFLAGS = -Wall -Werror -Wextra

SRCS = pipex.c pipex_check.c basic_functions.c ft_split.c\
		GNL/get_next_line.c GNL/get_next_line_utils.c

B_SRCS = bonus/multi_pipes_bonus.c bonus/GNL/get_next_line.c bonus/GNL/get_next_line_utils.c\
		bonus/pipex_check.c bonus/basic_functions.c bonus/ft_split.c bonus/pipex_bonus.c

OBJS = ${SRCS:.c=.o}

B_OBJS = ${B_SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

bonus:	$(B_NAME)

$(B_NAME):	$(B_OBJS)
		$(CC) $(B_OBJS) -o $(B_NAME)

clean:
		$(RM) $(OBJS) $(B_OBJS)

fclean: clean
		$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
