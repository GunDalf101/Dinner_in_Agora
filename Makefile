NAME = philo
NAMEBNS = philobonus
SOURCES = philo.c \
		myatoi.c\
		errorhandle.c \
		initer.c \
		timer.c \
		ruler.c \
		boring_routine.c
SOURCESBNS = philo_bonus.c \
		myatoi_bonus.c\
		errorhandle_bonus.c \
		initer_bonus.c \
		timer_bonus.c \
		ruler_bonus.c \
		monitoring_threads_bonus.c \
		boring_routine_bonus.c \

MAN_SRC_DIR = philo_man/philo_src
MAN_OBJ_DIR = philo_man/philo_obj
BONUS_SRC_DIR = philo_bonus/philo_src
BONUS_OBJ_DIR = philo_bonus/philo_obj
OBJECTS = $(patsubst %,$(MAN_OBJ_DIR)/%,$(SOURCES:%.c=%.o))
OBJECTSBNS = $(patsubst %,$(BONUS_OBJ_DIR)/%,$(SOURCESBNS:%.c=%.o))
INCLUDES = philo.h

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: elderscroll $(NAME)
	@if [ $$? -eq 0 ]; then \
		echo "\033[3m\033[1m\033[42m\033[31m~~Nothing to be done for 'all' anymore~~\033[0m"; \
	fi

bonus: elderscroll $(NAMEBNS)
	@if [ $$? -eq 0 ]; then \
		echo "\033[3m\033[1m\033[42m\033[31m~~Nothing to be done for 'bonus' anymore~~\033[0m"; \
	fi

$(NAME):$(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) $(CFLAGS)
	@echo "\033[47m\033[30m\033[1m             \`$@ linked\`             \033[0m"

$(NAMEBNS):$(OBJECTSBNS)
	@$(CC) -o $@ $(OBJECTSBNS) $(CFLAGS)
	@echo "\033[47m\033[30m\033[1m            \`$@ linked\`              \033[0m"

$(BONUS_OBJ_DIR)/%_bonus.o: $(BONUS_SRC_DIR)/%_bonus.c philo_bonus/philo_src/philo_bonus.h
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo "\033[33m$< compiled \033[0m"

$(MAN_OBJ_DIR)/%.o: $(MAN_SRC_DIR)/%.c philo_man/philo_src/philo.h
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo "\033[33m$< compiled \033[0m"

clean:
	@rm -f $(OBJECTS) $(OBJECTSBNS)
	@echo "\033[3m\033[1m\033[42m\033[31m~~   The objects have been cleaned   ~~\033[0m"; \
	
fclean: clean
	@rm -f $(NAME) $(NAMEBNS)
	@echo "\033[3m\033[1m\033[42m\033[31m~~The directory have been fully wiped~~\033[0m"; \

re: fclean all

.PHONY: all bonus clean fclean re

elderscroll:
	@echo '                                             _______________________'
	@echo '   _______________________-------------------                        \'
	@echo ' /:--__                                                              |'
	@echo '||< > |                                   ___________________________/'
	@echo '| \__/_________________-------------------                         |'
	@echo '|                                                                  |'
	@echo ' |                  THE SCROLL OF INFINITE WISDOM                   |'
	@echo ' |                                                                  |'
	@echo ' |       Three Rings for the Elven-kings under the sky,             |'
	@echo '  |        Seven for the Dwarf-lords in their halls of stone,        |'
	@echo '  |      Nine for Mortal Men doomed to die,                          |'
	@echo '  |        One for the Dark Lord on his dark throne                  |'
	@echo '  |      In the Land of Mordor where the Shadows lie.                 |'
	@echo '   |       One Ring to rule them all, One Ring to find them,          |'
	@echo '   |       One Ring to bring them all and in the darkness bind them   |'
	@echo '   |     In the Land of Mordor where the Shadows lie.                |'
	@echo '  |               "Whom who philosophizes heretisizes"               |'
	@echo '  |                                          ~imam Al Ghazali        |'
	@echo '  |                                                                  |'
	@echo '  |                                             -----------          |'
	@echo '  |                                            )) GunDalf ((         |'
	@echo '  |                                             -----------          |'
	@echo '  |                                              ____________________|_'
	@echo '  |  ___________________-------------------------                       \'
	@echo '  |/ --_                                                                 |'
	@echo '  ||[ ]||                                            ___________________/'
	@echo '   \===/___________________--------------------------'
	@echo ''