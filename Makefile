CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=minishell
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

OBJS=$(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LIBS)
	@echo "$(GREEN)Minishell compiled successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling $<...$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null
	@echo "$(GREEN)Libft compiled successfully.$(RESET)"

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR) > /dev/null
	@echo "$(YELLOW)Object files cleaned.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "$(RED)Executable cleaned.$(RESET)"