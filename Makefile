NAME = ircserv

SRCS = main.cpp Server.cpp

INCS = Server.hpp

OBJS = $(addprefix objs/, $(SRCS:.cpp=.o))

DEPS = $(wildcard objs/*.d)

CXX = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

objs/%.o:	srcs/%.cpp
			@ [ -d objs ] || mkdir -p objs
			$(CXX) $(CFLAGS) -MMD -c $< -o $@ -I./includes

$(NAME):	$(OBJS)
			$(CXX) -o $@ $^ -fsanitize=address

all: 		$(NAME)

clean:
			$(RM)r $(OBJS) $(DEPS) objs

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

include		$(DEPS)
