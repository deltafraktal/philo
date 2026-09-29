# ══════════════════════════════════════════════════════════════════════════════
#   philo — Makefile
# ══════════════════════════════════════════════════════════════════════════════

NAME        =  philo
NAME_B      =  philo_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
SRC_DIR     = src
SRC_B_DIR   = src/bonus
OBJ_DIR     = obj
OBJ_B_DIR   = obj/bonus

# ── Colors ────────────────────────────────────────────────────────────────────
END         := \033[0m
BOLD        := \033[1m
GREEN       := \033[32m
BLUE        := \033[34m
PURPLE      := \033[35m
YELLOW      := \033[33m

# ──────────────────────────────────────────────────────────────────────────────

SRCS        = \
    $(SRC_DIR)/main.c \

SRCS_B		= \

OBJ         = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_B       = $(SRCS_B:$(SRC_B_DIR)/%.c=$(OBJ_B_DIR)/%.o)

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

# ── Targets ───────────────────────────────────────────────────────────────────

all: $(NAME) ascii

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(BOLD)$(BLUE)🔗 Linking executable...$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✔ $(NAME) built successfully$(END)"

# ── Targets bonus ───────────────────────────────────────────────────────────────────
bonus: $(LIBFT) $(OBJ_B)
	@echo "$(BOLD)$(BLUE)🔗 Linking executable BONUS...$(END)"
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)
	@echo "$(BOLD)$(GREEN)✔ $(NAME_B) built BONUS successfully$(END)"
	@$(MAKE) ascii

# ── Compilation ───────────────────────────────────────────────────────────────

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@printf "$(BOLD)$(PURPLE)⚡ [%2d/%2d] Compiling %-30s$(END)" \
		$(CURRENT_FILE) $(TOTAL_FILES) "$<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo " $(GREEN)✓$(END)"

# ── Clean ─────────────────────────────────────────────────────────────────────

clean:
	@echo "$(BOLD)$(YELLOW)🧹 Cleaning objects...$(END)"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_B_DIR)

fclean: clean
	@echo "$(BOLD)$(YELLOW)🗑  Removing executable...$(END)"
	@$(RM) $(NAME)
	@$(RM) $(NAME_B)

superclean: fclean
	@echo "$(BOLD)$(YELLOW)BIG CLEANING...$(END)"
	@$(MAKE) -C libft fclean --silent

re: fclean all

# ── ASCII art ─────────────────────────────────────────────────────────────────

ascii:
	@echo "$(BOLD)$(PURPLE)"
	@if [ -f ascii_art.txt ]; then cat ascii_art.txt; fi
	@echo "$(END)"
	@echo "$(BOLD)$(GREEN)✨  philo is ready ✨$(END)"
	@echo "$(YELLOW)➜  use ./$(NAME) number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] $(END)"

.PHONY: all clean fclean re ascii mlx bonus superclean