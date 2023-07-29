NAME := minishell
SRCS :=	main.c str.c tokenizer.c list.c syntax.c heredoc.c parser.c minishell.c\
		libft/allocate.c libft/copy.c libft/is_number.c libft/is_alphabet.c
OBJS := $(SRCS:%.c=%.o)
ARCS := 
LIBS := $(dir $(ARCS))
CFLAGS = -Wextra -Werror -Wall
READLINE_LINK = -L $(shell brew --prefix readline)/lib -lreadline
READLINE_COM = -I $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(ARCS) $(OBJS)
	$(CC) $(CFLAGS) $(READLINE_LINK) $(DEBUG) $(OBJS) $(ARCS) -o $(NAME) -I.

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(READLINE_COM) $(DEBUG) -c -o $@ $< -I.

$(ARCS):
	make -C $(@D) DEBUG="$(DEBUG)"

clean:
	rm -f $(OBJS)
	$(foreach dir, $(LIBS), make -C $(dir) clean;)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re