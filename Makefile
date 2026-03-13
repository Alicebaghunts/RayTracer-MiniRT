MAKEFLAGS += --no-print-directory

NAME = miniRT

SRC_DIR   = source
OBJ_DIR   = build
INC_DIR   = includes
LIB_DIR   = libs

LIBFT_DIR    = $(LIB_DIR)/libft
MLX_MAC_DIR  = $(LIB_DIR)/minilibx_macos
MLX_LIN_DIR  = $(LIB_DIR)/minilibx-linux

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/initialization/initialization.c \
	$(SRC_DIR)/initialization/objects/init_ambient.c \
	$(SRC_DIR)/initialization/objects/init_camera.c \
	$(SRC_DIR)/initialization/objects/init_light.c \
	$(SRC_DIR)/initialization/objects/init_sphere.c \
	$(SRC_DIR)/initialization/objects/init_plane.c \
	$(SRC_DIR)/initialization/objects/init_cylinder.c \
	$(SRC_DIR)/initialization/objects/init_cone.c \
	$(SRC_DIR)/validation/validation.c \
	$(SRC_DIR)/validation/objects/ambient.c \
	$(SRC_DIR)/validation/objects/camera.c \
	$(SRC_DIR)/validation/objects/light.c \
	$(SRC_DIR)/validation/objects/sphere.c \
	$(SRC_DIR)/validation/objects/plane.c \
	$(SRC_DIR)/validation/objects/cylinder.c \
	$(SRC_DIR)/validation/objects/cone.c \
	$(SRC_DIR)/validation/utils/checking_nums.c \
	$(SRC_DIR)/validation/utils/checking_object.c \
	$(SRC_DIR)/validation/utils/file_handler_utils.c \
	$(SRC_DIR)/validation/utils/file_handler.c \
	$(SRC_DIR)/validation/utils/main_utils.c \
	$(SRC_DIR)/validation/utils/destroy.c \
	$(SRC_DIR)/validation/utils/utils.c \
	$(SRC_DIR)/initialization/utils/free_scene.c \
	$(SRC_DIR)/initialization/utils/free_objects.c \
	$(SRC_DIR)/initialization/utils/init_objects.c \
	$(SRC_DIR)/initialization/utils/normalize.c \
	$(SRC_DIR)/initialization/utils/normalize_utils.c \
	$(SRC_DIR)/initialization/utils/normalize_normals.c \
	$(SRC_DIR)/initialization/utils/init_texture.c \
	$(SRC_DIR)/initialization/utils/init_mlx.c \
	$(SRC_DIR)/ray_tracing/shade/shadow.c \
	$(SRC_DIR)/ray_tracing/shade/shade.c \
	$(SRC_DIR)/ray_tracing/shade/shade_utils.c \
	$(SRC_DIR)/ray_tracing/thread/thread_utils.c \
	$(SRC_DIR)/ray_tracing/thread/thread.c \
	$(SRC_DIR)/ray_tracing/drawing/intersect.c \
	$(SRC_DIR)/ray_tracing/drawing/drawing.c \
	$(SRC_DIR)/ray_tracing/drawing/ligthing.c \
	$(SRC_DIR)/ray_tracing/bump/bump.c \
	$(SRC_DIR)/ray_tracing/bump/sphere_bump.c \
	$(SRC_DIR)/ray_tracing/bump/texture.c \
	$(SRC_DIR)/ray_tracing/checkerboard/cone_checkerboard.c \
	$(SRC_DIR)/ray_tracing/checkerboard/cylinder_checkerboard.c \
	$(SRC_DIR)/ray_tracing/checkerboard/plane_checkerboard.c \
	$(SRC_DIR)/ray_tracing/checkerboard/sphere_checkerboard.c \
	$(SRC_DIR)/ray_tracing/utils/utils.c \
	$(SRC_DIR)/ray_tracing/utils/mlx_utils.c \
	$(SRC_DIR)/ray_tracing/utils/cylinder_utils.c \
	$(SRC_DIR)/ray_tracing/utils/cone_utils.c \
	$(SRC_DIR)/ray_tracing/utils/angle_utils.c \
	$(SRC_DIR)/formulas/cylinder/cylinder_caps.c \
	$(SRC_DIR)/formulas/cylinder/cylinder_disk.c \
	$(SRC_DIR)/formulas/cylinder/cylinder_shadow.c \
	$(SRC_DIR)/formulas/cylinder/cylinder_side.c \
	$(SRC_DIR)/formulas/cylinder/cylinder_intersect.c \
	$(SRC_DIR)/formulas/plane/plane_intersect.c \
	$(SRC_DIR)/formulas/cone/cone_intersect.c \
	$(SRC_DIR)/formulas/cone/cone_intersect_utils.c \
	$(SRC_DIR)/formulas/sphere/sphere_intersect.c \
	$(SRC_DIR)/formulas/vector/vector_formulas.c \
	$(SRC_DIR)/formulas/formulas.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin) 
    MLX_DIR   = $(MLX_MAC_DIR)
    INCS      = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
    LIBS      = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx
    FFLAGS    = -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S),Linux)
    MLX_DIR   = $(MLX_LIN_DIR)
    INCS      = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
    LIBS      = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
    FFLAGS    =
endif

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling \033[0;33m$<\033[0m"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: lib mlx $(NAME)

$(NAME): $(OBJS)
	@echo "Linking \033[0;32m$(NAME)\033[0m"
	@$(CC) $(OBJS) $(LIBS) $(FFLAGS) -o $(NAME)

lib:
	@$(MAKE) -C $(LIBFT_DIR)

mlx:
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_MAC_DIR) clean 2>/dev/null || true
	@$(MAKE) -C $(MLX_LIN_DIR) clean 2>/dev/null || true
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette $(INC_DIR) $(SRC_DIR) $(LIBFT_DIR) 2>/dev/null || true

.PHONY: all clean fclean re lib mlx norm