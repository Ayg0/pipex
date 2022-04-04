CC = cc
NAME = pipex


CFLAGS = -Wall -Werror -Wextra -g

SRCS = pipex.c pipex_utils.c pipex_utils2.c ft_split.c pipex_bonus.c\
		 GNL/get_next_line.c GNL/get_next_line_utils.c\
		 multi_pipes.c

OBJS = ${SRCS:.c=.o}


.c.o:
		$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
