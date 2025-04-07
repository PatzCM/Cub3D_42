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

# Header files
HEADERS = $(INC_PATH)/cub3d.h

# Source files

SRCS = ${addprefix ${SRCS_PATH}/, \
			 main.c \
			 parsing.c \
			 init_data.c \ }

# Object files
OBJS = ${addprefix ${SRC_PATH}/, ${notdir $(SRCS:.c=.o)}}

# Libraries
LIBS = ${addprefix ${LIB_PATH}/, \
			libft.a \
			mlx.a}

#------------------------------------------------------------------------------#
#															COMPILER & FLAGS                                 #
#------------------------------------------------------------------------------#

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar

#-----------------------------------------------------------------------------#
#                              RULES                                          #
#-----------------------------------------------------------------------------#

# All
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

${NAME}: ${OBJS} ${LIBS}
	@echo "$(GREEN)$(BOLD)$(BUILD) $(NAME)$(RESET)"
	@${CC} ${CFLAGS} -o $@ $^
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

${BUILD_PATH}/%.o: ${SRC_PATH}/%.c ${HEADERS}
	@mkdir -p ${BUILD_PATH}
	@echo "$(GREEN)$(BOLD)$(BUILD) $(NAME)$(RESET)"
	@${CC} ${CFLAGS} -I ${INC_PATH} -c $< -o $@
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

deps:
	@echo "$(GREEN)$(BOLD)$(BUILD) $(NAME)$(RESET)"
	@${CC} ${CFLAGS} -I ${INC_PATH} -MD -c $< -o $@
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

clean:
	@echo "$(RED)$(BOLD)$(CLEAN) $(NAME)$(RESET)"
	@${RM} ${BUILD_PATH}
	@echo "$(RED)$(BOLD)$(CROSS) $(NAME) $(RED)$(BOLD)$(CLEAN)$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)$(CLEAN) $(NAME)$(RESET)"
	@${RM} ${NAME}
	@echo "$(RED)$(BOLD)$(CROSS) $(NAME) $(RED)$(BOLD)$(CLEAN)$(RESET)"

re: fclean all
	@echo "$(GREEN)$(BOLD)$(BUILD) $(NAME)$(RESET)"
	@${CC} ${CFLAGS} -o $@ $^
	@echo "$(GREEN)$(BOLD)$(CHECKMARK) $(NAME) $(GREEN)$(BOLD)$(BUILD)$(RESET)"

.PHONY: all clean fclean re


