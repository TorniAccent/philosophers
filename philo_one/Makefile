NAME	= philo_one

SRCS	=	srcs/core.c srcs/threading.c srcs/main.c srcs/init.c srcs/utils.c srcs/parser.c

OBJS	=	core.o threading.o main.o init.o utils.o parser.o

OBJS_D	=	objs/core.o objs/threading.o objs/main.o objs/init.o objs/utils.o objs/parser.o

CC		= gcc -Wall -Wextra -Werror -pthread

INCLUDES = -I includes

.PHONY: all clean fclean re

all: objs $(NAME)

objs:
	mkdir objs

objs/%.o: srcs/%.c
	$(CC) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS_D)
	$(CC) $(OBJS_D) $(INCLUDES) -o $(NAME)

clean:
	/bin/rm -rf objs 
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
