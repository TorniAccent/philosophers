NAME	= philo_one

SRCS	= srcs/core.c srcs/threading.c srcs/init.c srcs/utils.c srcs/parser.c srcs/main.c

OBJS	= core.o threading.o init.o utils.o time.o

OBJS_D	= objs/core.o objs/threading.o objs/init.o objs/utils.o objs/parser.o objs/main.o

CC		= gcc -pthread

FLAGS	= \
			-Wall -Wextra -Werror

INCLUDES = -I includes

.PHONY: all clean fclean re

all: objs $(NAME)

objs:
	mkdir objs

objs/%.o: srcs/%.c
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS_D)
	$(CC) $(FLAGS) $(OBJS_D) $(INCLUDES) -o $(NAME)

clean:
	/bin/rm -rf objs 
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
