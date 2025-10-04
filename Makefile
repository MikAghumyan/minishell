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

# Source files per folder
SRCS_MAIN = \
	src/main.c \
	src/initializer.c \
	src/handlers.c
SRCS_AST = \
	src/ast/ast.c \
	src/ast/ast_build.c \
	src/ast/ast_build_utils.c \
	src/ast/ast_parse_command.c \
	src/ast/ast_parse_subshell.c \
	src/ast/ast_collect_args.c \
	src/ast/ast_parse_redirects.c
SRCS_ENV = \
	src/env/env.c \
	src/env/env_utils.c
SRCS_EXECUTOR = \
	src/executor/ast_command_execute_utils.c \
	src/executor/ast_executor.c \
	src/executor/ast_find_command_path.c \
	src/executor/ast_logical_utils.c \
	src/executor/ast_pipe_utils.c \
	src/executor/ast_pipe_utils2.c \
	src/executor/ast_redirect_utils.c \
	src/executor/ast_subshell_execute_utils.c
SRCS_TOKENIZER = \
	src/tokenizer/expander.c \
	src/tokenizer/syntax_analyzer.c \
	src/tokenizer/token_type_utils.c \
	src/tokenizer/token_utils.c \
	src/tokenizer/token_word_utils.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/collect_redirects.c

# Combine all sources
SRCS = $(SRCS_MAIN) $(SRCS_AST) $(SRCS_ENV) $(SRCS_EXECUTOR) $(SRCS_TOKENIZER)

# Object files
OBJDIR=obj
OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEBUG_OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.c=.debug.o))

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LIBS)
	@echo "$(GREEN)Minishell compiled successfully.$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling $<...$(RESET)"

$(OBJDIR)/%.debug.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@
	@echo "$(MAGENTA)Compiling $< (debug)...$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) complete > /dev/null
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