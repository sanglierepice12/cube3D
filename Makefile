# ===================== #
#       VARIABLES       #
# ===================== #

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Compiler and Flags
CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g3 -fsanitize=leak -fsanitize=address -Iinclude

# Executable
NAME = cub3d

# Directories
SRC_DIR = ./sources
OBJ_DIR = ./obj
DEP_DIR = ./dep

# Source Files
SRC = main.c get_map.c draw_tools.c hooks.c init.c mini_map.c

GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# Path to MiniLibX
MINILIBX_URL = https://cdn.intra.42.fr/document/document/23121/minilibx-linux.tgz
MINILIBX_DIR = minilibx-linux
MINILIBX_LIB = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

# Object and Dependency Files
SRCS = $(addprefix $(SRC_DIR)/, $(SRC)) $(GNL_SRC)
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))

# ===================== #
#       COMMANDS        #
# ===================== #

# Default target
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

# Compile the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MINILIBX_LIB) -o $(NAME)

# Compile each .c file to .o and generate .d files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D) $(DEP_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$*.d  # Déplace le .d généré dans le dossier DEP_DIR

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

# Include the dependency files
-include $(DEPS)

.PHONY: all clean fclean re $(MINILIBX_DIR)
