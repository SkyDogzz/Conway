CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR) -g3
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

_END    = $(shell printf "\033[0m")
_BOLD   = $(shell printf "\033[1m")
_CYAN   = $(shell printf "\033[36m")
_BLUE   = $(shell printf "\033[34m")

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
MLX_DIR = .minilibx-linux
LIBFT_GIT = https://github.com/SkyDogzz/ft_ft.git
MLX_GIT = https://github.com/42paris/minilibx-linux.git

SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(_CYAN)[COMPILATION]$(_END) Création de l'objet : $@ ⚙️"
INC_FILES = $(INC_DIR)/conway.h

NAME = conway

all: init libft $(NAME)
	@echo "$(_CYAN)[BUILD COMPLET]$(_END) $(NAME) est prêt ! 🚀"

init:
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(_BLUE)[INIT]$(_END) Clonage de libft..."; \
		git clone $(LIBFT_GIT) $(LIBFT_DIR); \
	fi
	@make -C $(LIBFT_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(_BLUE)[INIT]$(_END) Clonage de minilibx..."; \
		git clone $(MLX_GIT) $(MLX_DIR); \
	fi
	@make -C $(MLX_DIR)

libft:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	@echo "$(_CYAN)[LINKING]$(_END) $(NAME) est créé ! 🔗"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(_CYAN)[COMPILATION]$(_END) Création de l'objet : $@ ⚙️"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean || true
	@make -C $(MLX_DIR) clean || true
	@echo "$(_BLUE)[CLEAN]$(_END) Suppression des fichiers objets 🧹"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "$(_BLUE)[FCLEAN]$(_END) Suppression de $(NAME) 🗑️"

re: fclean all

lint:
	cppcheck $(SRC_DIR) --enable=all --suppress=unusedFunction \
		--suppress=variableScope --suppress=missingIncludeSystem \
		2>&1 > /dev/null

.PHONY: all clean fclean re ascii init libft lint

