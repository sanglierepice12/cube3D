# ===================== #
#       VARIABLES       #
# ===================== #

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

# Compiler and Flags
CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -g3  -O3 -Iinclude -I/opt/X11/include #-fsanitize=leak -fsanitize=address
LDFLAGS = -L/opt/X11/lib -lX11 -lXext -lm

# Executable
NAME = cub3D

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
DEP_DIR = ./dep

# Source Files
SRC =	main.c													\
		parsing/init_struct.c									\
		parsing/init_the_map/get_map.c							\
		parsing/init_the_map/get_text_rgb.c						\
		parsing/init_the_map/check_parse/is_lineok.c			\
		parsing/init_the_map/check_parse/check_rgb.c			\
		parsing/init_the_map/check_parse/check_textures.c		\
		parsing/init_the_map/fill_struct_map/fill_map_struct.c	\
		parsing/init_the_map/fill_struct_map/fill_map_suit.c	\
		parsing/get_next_line/get_next_line.c					\
		parsing/get_next_line/get_next_line_utils.c				\
		parsing/check_map_validity/eyes_to_map.c				\
		exec/constants.c										\
		exec/draw_utils.c										\
		exec/draw.c										\
		exec/exec_utils.c										\
		exec/init.c												\
		exec/mini_map.c											\
		exec/render_3d_map.c									\
		exec/hook_event/hooks.c									\
		exec/hook_event/hooks_managment.c						\
		utils/utils.c											\
		utils/calloc.c											\
		utils/compare.c											\
		utils/linked_list.c										\
		utils/split.c											\
		utils/atoi.c											\
		utils/exit_free/exit.c									\
		utils/exit_free/free_parse.c							\
		utils/exit_free/free_exec.c								\
		utils/exit_free/free2.c									\

# Path to MiniLibX
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
	@$(MAKE) -C $(MINILIBX_DIR)

-include $(DEPS)

# Compile the executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MINILIBX_LIB) -o $(NAME) $(LDFLAGS)

# Compile each .c file to .o and generate .d files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(OBJ_DIR)/parsing $(DEP_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/parsing/init_the_map $(DEP_DIR)/parsing/init_the_map
	@mkdir -p $(OBJ_DIR)/parsing/check_map_validity $(DEP_DIR)/parsing/check_map_validity
	@mkdir -p $(OBJ_DIR)/parsing/init_the_map/check_parse $(DEP_DIR)/parsing/init_the_map/check_parse
	@mkdir -p $(OBJ_DIR)/parsing/init_the_map/fill_struct_map $(DEP_DIR)/parsing/init_the_map/fill_struct_map
	@mkdir -p $(OBJ_DIR)/parsing/get_next_line $(DEP_DIR)/parsing/get_next_line
	@mkdir -p $(OBJ_DIR)/exec $(DEP_DIR)/exec
	@mkdir -p $(OBJ_DIR)/exec/hook_event $(DEP_DIR)/exec/hook_event
	@mkdir -p $(OBJ_DIR)/utils $(DEP_DIR)/utils
	@mkdir -p $(OBJ_DIR)/utils/exit_free $(DEP_DIR)/utils/exit_free
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@
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
