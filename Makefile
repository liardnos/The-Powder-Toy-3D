##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile for bistro-matic
##

SRC		=		src/*.cpp			\



NAME	=		3D_powder

FLAGS	= -I./SFML-2.5.1_gcc/include

LINKER	= -L./lib -lmy -lm -L./SFML-2.5.1_gcc/lib -lsfml-graphics -lsfml-window -lsfml-system

#-Wl, -rpath=./SFML-2.5.1_gcc/lib
#-fno-diagnostics-show-labels -fno-diagnostics-show-labels fdiagnostics-generate-patch -Wall -Wextra
#fsyntaxe-only


all:

	make -C ./lib build
	g++ -c $(SRC) $(FLAGS)

	g++ *.o -o $(NAME) $(LINKER)
	export LD_LIBRARY_PATH=./SFML-2.5.1_gcc/lib && ./$(NAME)
#-rpath-link=./SFML-2.5.1_gcc/lib

allO4:
	make -C ./lib buildO6
	gcc -o $(NAME) $(SRC) $(FLAGS) -Ofast

run: all
	make fclean
	./$(NAME)

runO4: allO4
	make fclean
	./$(NAME)

clean:
	rm -f $(OBJ)
	make -C ./lib clean
	rm -f *.html
	rm -f *.gcno
	rm -f *.gcda

fclean:	clean
	rm -f $(NAME)
	make -C ./lib fclean
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.html
	rm -f vgcore.*
	rm -f callgrind.*
	rm -f *.o
	rm -f libmy.a

clear:
	clear

re: clear fclean all

valgrind: fclean
	clear
	make -C ./lib valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	valgrind -s --leak-check=full --track-origins=yes  --show-leak-kinds=definite ./$(NAME) #&> valgrind_log

callgrind: fclean
	rm -f callgrind.*
	clear
	make -C ./lib valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	-valgrind --tool=callgrind ./$(NAME) 3 #&> valgrind_log
	-kcachegrind callgrind.*

callgrindO6: fclean
	rm -f callgrind.*
	clear
	make -C ./lib buildO6
	gcc -g -o $(NAME) $(SRC) $(FLAGS) -O6
	-valgrind --tool=callgrind ./$(NAME) 3 #&> valgrind_log
	-kcachegrind callgrind.*
