INCCORE=./core/

NAME = pipex

SRC = $(INCCORE)pipex.c $(INCCORE)split.c $(INCCORE)function.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:%.c=%.o)

all: $(NAME)

RM = rm -rf

$(NAME):	$(OBJS)
		gcc $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf *.o
	rm -rf $(INCCORE)*.o

fclean:
	rm -rf $(NAME)
	rm -rf *.o
	rm -rf $(INCCORE)*.o

re: clean $(NAME)

.phony: all clean fclean re
