SRC = 	main.cpp\
		core/core.cpp\
		core/util/logger.cpp\
		core/util/velocity.cpp\
		core/engine/map.cpp\
		core/engine/seed.cpp\
		core/engine/base/base.cpp\
		core/engine/base/entity.cpp\
		core/entity/chunck.cpp\
		core/entity/partical.cpp\
		core/entity/player.cpp

CC		= g++
NAME 	= game
OBJO 	= $(SRC:%.cpp=%.o)
OBJC 	= $(SRC)
FLAG	= -static -static-libgcc -static-libstdc++
LIBFLAG = -L"C:/Users/Paris/Desktop/subV/git/littleBigGame/SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system

define execute-command
$(CC) $(1)

endef

all:	$(NAME)

$(NAME):
	$(foreach d, $(OBJC), $(call execute-command,-c $d -o $(d:%.cpp=%.o) -ISFML/include -Icore))
	$(CC) $(FLAG) $(OBJO) -o $(NAME) -ISFML/include $(LIBFLAG)

clean:
	rm -f $(OBJO)

fclean:		clean
	rm -f $(NAME) $(NAME).exe
	
re:	fclean all