CC=cc
CFLAGS=-Wall -Wextra -Werror $(EXTRA_FLAGS)
DEBUG_FLAGS=-g -fsanitize=address,undefined
NAME=minishell
NAME_DEBUG=minishell_debug
LIBFT=libft.a
LIBFT_DIR=libft
LIBS=-lreadline

GREEN=\033[0;32m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RED=\033[0;31m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

SRCS=src/main.c \
	  src/initializer.c \
	  src/tokenizer/tokenizer.c \
	  src/tokenizer/token_utils.c \
	  src/tokenizer/token_type_utils.c \
	  src/handlers.c \
	  src/env/env.c \
	  src/env/env_utils.c \

OBJS=$(SRCS:.c=.o)
DEBUG_OBJS=$(SRCS:.c=.debug.o)

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LIBS)
	@echo "$(GREEN)Minishell compiled successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling $<...$(RESET)"

%.debug.o: %.c
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@
	@echo "$(MAGENTA)Compiling $< (debug)...$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)Libft compiled successfully.$(RESET)"

debug: $(DEBUG_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(NAME_DEBUG) $(DEBUG_OBJS) $(LIBFT_DIR)/$(LIBFT) $(LIBS)
	@echo "$(GREEN)Minishell debug version compiled successfully.$(RESET)"
	@echo "$(CYAN)Run with: ./$(NAME_DEBUG)$(RESET)"

clean:
	@rm -f $(OBJS) $(DEBUG_OBJS)
	@make clean -C $(LIBFT_DIR) > /dev/null
	@echo "$(YELLOW)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_DEBUG)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "$(RED)Executable cleaned.$(RESET)"

re: fclean all

debug_re: fclean debug