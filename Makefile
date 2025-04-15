#======================================================================#
#                     CUB3D - A C++ 3D Game Engine                     #
#======================================================================#

# This file is part of CUB3D.
NAME = cub3D

#------------------------------------------------------------------------------#
#															COLORS & STYLES                                	 #
#------------------------------------------------------------------------------#

# Colors
WHITE		= \033[0;37m
YELLOW		= \033[0;33m
CYAN		= \033[0;36m
GREEN		= \033[0;32m
RED			= \033[0;31m
PURPLE		= \033[0;35m
BLUE		= \033[0;34m
RESET		= \033[0m

# Styles
BOLD		= \033[1m
UNDERLINE	= \033[4m
ITALIC		= \033[3m
REVERSE		= \033[7m
# BOLD UNDERLINE	= \033[1;4m
#
#Emojis

CHECK = ✓
CLEAN = 🧹
BUILD = 🔨
ROCKET = 🚀
BOOK = 📚
SPARKLES = ✨
CHECK = 
CHECKMARK = ✔️
CROSS = ❌

#------------------------------------------------------------------------------#
#															FILES & PATHS                                	 	 #
#------------------------------------------------------------------------------#

# Source files
SRC_PATH = srcs
INC_PATH = incs
LIB_PATH = libs
BUILD_PATH = .build

# Header files
HEADERS = $(INC_PATH)/cub3d.h

# Source files

SRCS = $(addprefix $(SRC_PATH)/, \
			 main.c \
			 parsing.c \
			 init_data.c)

# Object files
OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))

# Libraries
LIBS = $(addprefix $(LIB_PATH)/, \
			libft/libft.a \
			mlx/libmlx.a)

#------------------------------------------------------------------------------#
#															COMPILER & FLAGS                                 #
#------------------------------------------------------------------------------#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
AR = ar

#-----------------------------------------------------------------------------#
#                              RULES                                          #
#-----------------------------------------------------------------------------#

# All
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) BUILD COMPLETED $(GREEN)$(BOLD)$(BUILD)$(RESET)"

${NAME}: ${OBJS} ${LIBS}
	@echo "$(GREEN)$(BOLD)$(BUILD) BUILDING...$(RESET)"
	@${CC} ${CFLAGS} -o $@ $(OBJS) -L$(LIB_PATH)/libft -lft -L$(LIB_PATH)/mlx -lmlx

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(BUILD_PATH)
	@$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

# Build libft
$(LIB_PATH)/libft/libft.a:
	@echo "$(GREEN)$(BOLD)Building libft$(RESET)"
	@$(MAKE) -C $(LIB_PATH)/libft

# Build mlx
$(LIB_PATH)/mlx/libmlx.a:
	@echo "$(GREEN)$(BOLD)Building mlx$(RESET)"
	@$(MAKE) -C $(LIB_PATH)/mlx

deps:
	@echo "$(GREEN)$(BOLD)$(BUILD) INCLUDED HEADERS $(RESET)"
	@${CC} ${CFLAGS} -I ${INC_PATH} -MD -c $< -o $@
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

clean:
	@echo "$(RED)$(BOLD)$(CLEAN) CLEANING FILES... $(RESET)"
	@${RM} ${BUILD_PATH}
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS CLEANING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)$(CLEAN) REMOVING EXECUTER... $(RESET)"
	@${RM} ${NAME}
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) SUCCESS REMOVING! $(GREEN)$(BOLD)$(CLEAN)$(RESET)"

re: 
	@echo "$(GREEN)$(BOLD)$(BUILD) REBUILDING !$(RESET)"
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re


