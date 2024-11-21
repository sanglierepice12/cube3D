# ===================== #
#       VARIABLES       #
# ===================== #

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Compiler and Flags
CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g3 -Iinclude  #-fsanitize=leak -fsanitize=address
LDFLAGS = -lm

# Executable
NAME = cub3d

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
DEP_DIR = ./dep

# Source Files
SRC =	main.c										\
		parsing/get_map.c							\
		exec/draw_utils.c							\
		exec/hook_event/hooks.c						\
		exec/hook_event/hooks_managment.c			\
		exec/init.c									\
		exec/mini_map.c								\
		exec/exec_utils.c							\
		exec/render_3d_map.c						\
		parsing/get_next_line/get_next_line.c		\
		parsing/get_next_line/get_next_line_utils.c

#GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# Path to MiniLibX
MINILIBX_URL = https://cdn.intra.42.fr/document/document/23121/minilibx-linux.tgz
MINILIBX_DIR = minilibx-linux
MINILIBX_LIB = -L$(MINILIBX_DIR) -lmlx -lXext -lX11

# Object and Dependency Files
#SRCS = $(addprefix $(SRC_DIR)/, $(SRC)) $(GNL_SRC)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(DEP_DIR)/, $(SRC:.c=.d))

# ===================== #
#       COMMANDS        #
# ===================== #

# Target
.SILENT: all clean fclean re

all: $(MINILIBX_DIR) $(NAME)
	@echo "$(GREEN)Compilation of $(NAME) completed successfully!$(NC)"

# MiniLibX - download and compile if needed
$(MINILIBX_DIR):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		echo "$(GREEN)Downloading MiniLibX...$(NC)"; \
		curl -o minilibx-linux.tgz $(MINILIBX_URL); \
		tar -xzf minilibx-linux.tgz; \
		rm -f minilibx-linux.tgz; \
	fi
	@$(MAKE) -C $(MINILIBX_DIR)

-include $(DEPS)

# Compile the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MINILIBX_LIB) -o $(NAME) $(LDFLAGS) -Iminilibx-linux

# Compile each .c file to .o and generate .d files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(OBJ_DIR)/parsing/get_next_line $(DEP_DIR)/parsing/get_next_line
	@mkdir -p $(OBJ_DIR)/parsing $(DEP_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/exec $(DEP_DIR)/exec
	@mkdir -p $(OBJ_DIR)/exec/hook_event $(DEP_DIR)/exec//hook_event
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@ -Iminilibx-linux
	@echo "$(GREEN)Compilation of $< completed!$(NC)"

# Clean object and dependency files
clean:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@$(MAKE) clean -C $(MINILIBX_DIR)
	@echo "$(RED)Cleanup completed!$(NC)"

# Full clean including executable
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable deleted!$(NC)"

# Rebuild
re: fclean all

.PHONY: all clean fclean re $(MINILIBX_DIR)
