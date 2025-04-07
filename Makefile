.PHONY: all clean fclean re run val san

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC_DIR = src/
OBJ_DIR = obj/
OBJSAN_DIR = obj_san/
DEP_DIR = dep/
INCLUDE_DIR = include/

DEP_FILE = $(DEP_DIR)$*.d
DEPFLAGS = -MMD -MF $(DEP_FILE)

C_FILE = \
	philo.c\
	utils.c\
	mutex.c\
	forks.c\
	init_philos.c\
	verif_death_and_eat_count.c\
	action/eat.c\
	action/sleep.c

SRC_FILE := $(addprefix $(SRC_DIR), $(C_FILE))

OBJ = $(C_FILE:.c=.o)
OBJ := $(addprefix $(OBJ_DIR), $(OBJ))

DEPS = $(C_FILE:%.c=$(DEP_DIR)%.d)

INC = -I $(INCLUDE_DIR)

all:
	$(MAKE) $(NAME)

$(NAME): .NotRelink

.NotRelink: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	touch .NotRelink

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(dir $(DEP_FILE))
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJSAN_DIR)

fclean:
	$(MAKE) clean
	rm -f $(NAME) $(NAME)_san .NotRelink

re:
	$(MAKE) fclean
	$(MAKE) all

run:
	clear
	$(MAKE)
	./$(NAME)

val:
	$(MAKE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

san:
	$(MAKE) NAME=$(NAME)_san OBJ_DIR=$(OBJSAN_DIR) CFLAGS="$(CFLAGS) -fsanitize=thread"
	TSAN_OPTIONS="second_deadlock_stack=1" ./$(NAME)_san
-include $(DEPS)
