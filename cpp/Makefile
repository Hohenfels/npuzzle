NAME		=	npuzzle
FLAGS		= 	-std=c++17 -Wall -Werror -Wextra -Ofast
COMPILER	=	g++

DIR_INC		=	./inc/
DIR_SRC		=	./src/
DIR_OBJ		= 	./obj/

HEAD_AVM	=	heuristic.h \
				Node.h \
				npuzzle.h \
				parser.h \
				solver.h

SRC_AVM		=	parser.cpp \
				checkSolvability.cpp \
				heuristics.cpp \
				Node.cpp \
				solver.cpp \
				main.cpp

#INC_PATH 	= 	$(addprefix $(DIR_INC), $(HEAD_AVM))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(SRC_AVM:.cpp=.o))
INC 		= 	$(addprefix -I, $(DIR_INC))

.PHONY: all obj $(NAME) clean fclean re

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp #$(INC_PATH)
	@$(COMPILER) $(FLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all