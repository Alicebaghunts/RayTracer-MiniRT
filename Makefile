MAKEFLAGS += --no-print-directory

NAME = miniRT

SRC_DIR         = source
OBJ_DIR         = build
LIB_DIR         = libs
INC_DIR         = includes

VALIDATION_DIR  = $(SRC_DIR)/validation
INITIALIZATION_DIR  = $(SRC_DIR)/initialization
PARSE_DIR       = $(SRC_DIR)/parse
GRAPHICS_DIR    = $(SRC_DIR)/graphics
RAY_TRACING_DIR = $(SRC_DIR)/ray_tracing
VECTOR_DIR      = $(SRC_DIR)/vector
FORMULAS_DIR	= $(SRC_DIR)/formulas
MINILIBX_DIR    = $(LIB_DIR)/minilibx_macos
LIBFT_DIR       = $(LIB_DIR)/libft

SRCS = \
	$(SRC_DIR)/main.c \
	$(VALIDATION_DIR)/validation.c \
	$(VALIDATION_DIR)/objects/ambient.c \
	$(VALIDATION_DIR)/objects/camera.c \
	$(VALIDATION_DIR)/objects/light.c \
	$(VALIDATION_DIR)/objects/sphere.c \
	$(VALIDATION_DIR)/objects/plane.c \
	$(VALIDATION_DIR)/objects/cylinder.c \
	$(VALIDATION_DIR)/objects/cone.c \
	$(VALIDATION_DIR)/utils/checking_nums.c \
	$(VALIDATION_DIR)/utils/checking_object.c \
	$(VALIDATION_DIR)/utils/file_handler_utils.c \
	$(VALIDATION_DIR)/utils/file_handler.c \
	$(VALIDATION_DIR)/utils/main_utils.c \
	$(INITIALIZATION_DIR)/initialization.c \
	$(INITIALIZATION_DIR)/objects/init_ambient.c \
	$(INITIALIZATION_DIR)/objects/init_camera.c \
	$(INITIALIZATION_DIR)/objects/init_light.c \
	$(INITIALIZATION_DIR)/objects/init_cylinder.c \
	$(INITIALIZATION_DIR)/objects/init_sphere.c \
	$(INITIALIZATION_DIR)/objects/init_plane.c \
	$(INITIALIZATION_DIR)/objects/init_cone.c \
	$(INITIALIZATION_DIR)/utils/free_scene.c \
	$(INITIALIZATION_DIR)/utils/free_objects.c \
	$(INITIALIZATION_DIR)/utils/init_objects.c \
	$(INITIALIZATION_DIR)/utils/normalize.c \
	$(INITIALIZATION_DIR)/utils/normalize_utils.c \
	$(INITIALIZATION_DIR)/utils/normalize_normals.c \
	$(INITIALIZATION_DIR)/utils/init_texture.c \
	$(INITIALIZATION_DIR)/utils/init_mlx.c \
	$(RAY_TRACING_DIR)/shade/shadow.c \
	$(RAY_TRACING_DIR)/shade/shade.c \
	$(RAY_TRACING_DIR)/shade/shade_utils.c \
	$(RAY_TRACING_DIR)/thread/thread_utils.c \
	$(RAY_TRACING_DIR)/thread/thread.c \
	$(RAY_TRACING_DIR)/drawing/intersect.c \
	$(RAY_TRACING_DIR)/drawing/drawing.c \
	$(RAY_TRACING_DIR)/drawing/ligthing.c \
	$(RAY_TRACING_DIR)/bump/bump.c \
	$(RAY_TRACING_DIR)/bump/sphere_bump.c \
	$(RAY_TRACING_DIR)/bump/texture.c \
	$(RAY_TRACING_DIR)/checkerboard/cone_checkerboard.c \
	$(RAY_TRACING_DIR)/checkerboard/cylinder_checkerboard.c \
	$(RAY_TRACING_DIR)/checkerboard/plane_checkerboard.c \
	$(RAY_TRACING_DIR)/checkerboard/sphere_checkerboard.c \
	$(RAY_TRACING_DIR)/utils/utils.c \
	$(RAY_TRACING_DIR)/utils/mlx_utils.c \
	$(RAY_TRACING_DIR)/utils/cylinder_utils.c \
	$(RAY_TRACING_DIR)/utils/cone_utils.c \
	$(RAY_TRACING_DIR)/utils/angle_utils.c \
	$(FORMULAS_DIR)/cylinder/cylinder_caps.c \
	$(FORMULAS_DIR)/cylinder/cylinder_disk.c \
	$(FORMULAS_DIR)/cylinder/cylinder_shadow.c \
	$(FORMULAS_DIR)/cylinder/cylinder_side.c \
	$(FORMULAS_DIR)/cylinder/cylinder_intersect.c \
	$(FORMULAS_DIR)/plane/plane_intersect.c \
	$(FORMULAS_DIR)/cone/cone_intersect.c \
	$(FORMULAS_DIR)/cone/cone_intersect_utils.c \
	$(FORMULAS_DIR)/sphere/sphere_intersect.c \
	$(FORMULAS_DIR)/vector/vector_formulas.c \
	$(FORMULAS_DIR)/formulas.c \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION -g3 -fsanitize=address

INCS  = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
LIBS  = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx
FMS   = -framework OpenGL -framework AppKit

UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	MINILIBX_DIR = $(LIB_DIR)/minilibx-linux
	INCS  = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
	LIBS  = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lm -lX11 -lXext
	FMS   =
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

$(NAME): mlx lib $(OBJS)
	@echo "Linking $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LIBS) $(FMS) -o $(NAME)

lib:
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MINILIBX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

norm:
	@norminette  $(shell find . -name "*.h" ! -path "./libs/minilibx*") source libs/libft 

re: fclean all

.PHONY: all clean fclean re lib mlx
