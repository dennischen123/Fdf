NAME = fdf

CFILES = src/main.c \
		 src/parse.c \
		 src/draw.c   \
 		 src/key_hook.c \
 		 src/projection.c

LIBS = libft.a \
	   minilibx/libmlx.a 

FRAMEWORKS = -framework OpenGL -framework AppKit

HEADERS = inc

all: $(CFILES) $(LIBS)
	@gcc -Wall -Wextra -Werror -o $(NAME) -I $(HEADERS) $(FRAMEWORKS) $(LIBS) $(CFILES)

debug: $(CFILES) $(LIBS)
	@gcc -g -o $(NAME) -I $(HEADERS) $(FRAMEWORKS) $(LIBS) $(CFILES)

clean :
	rm -f minilibx/*.o

fclean : clean
	rm -f fdf

re : fclean all