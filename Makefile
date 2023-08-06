NAME := minishell
SRCS :=	main.c\
		shell/minishell.c shell/env.c shell/env_util.c\
		parser/heredoc.c parser/tokenizer.c parser/syntax.c parser/compiler.c parser/unquote.c parser/process.c\
		libft/allocate.c libft/copy.c libft/is_number.c libft/is_alphabet.c\
		str/str.c\
		collection/list.c\
		pipe/execute_util.c pipe/execute.c pipe/pipe_envp.c pipe/pipe_execute.c\
		signal/signal.c\
		launcher/builtin/echo.c launcher/builtin/pwd.c launcher/builtin/exit.c launcher/builtin/cd.c launcher/builtin/export.c launcher/builtin/unset.c launcher/builtin/env.c

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
