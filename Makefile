CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=minishell
LIBFT=libft.a
LIBFT_DIR=libft

GREEN=\033[0;32m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RED=\033[0;31m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
RESET=\033[0m

OBJS=$(SRCS:.c=.o)
all: $(NAME)

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