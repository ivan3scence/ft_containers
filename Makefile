CC			= c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g -D MACOS=1
ifeq (${MAKECMDGOALS}, l)
CC 			=	c++	 -Wall -Wextra -Werror -g -fsanitize=address -D LINUX=1
endif
RM			= rm -rf
NAME		= ./vector
NAME_SHORT	= vector

INCS_DIR	= ./include/
MAIN_INC	= -I$(INCS_DIR)

INC			= vector.hpp iterator.hpp

INCS		= $(addprefix ${INCS_DIR}, ${INC})

SRCS_DIR 	= ./src/

SRC			= main.cpp vector/vector.cpp iterator/iterator.cpp

TMP_DIR 	= ./templates/

TMP 		= vector.tcc

TMPS		= $(addprefix ${TMP_DIR}, ${TMP})

SRCS		= $(addprefix ${SRCS_DIR}, ${SRC})

OBJS		= $(SRCS:.cpp=.o)

%.o			: %.cpp $(INCS) Makefile $(TMPS)
			$(CC) $(MAIN_INC) -c $< -o $@

all			: $(NAME)

l				: all

$(NAME)		: $(OBJS)
			$(CC) $(MAIN_INC) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		: clean
			$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
