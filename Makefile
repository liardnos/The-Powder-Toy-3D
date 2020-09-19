##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile for bistro-matic
##

SRC		=		src/*.cpp			\



NAME	=		3D_powder

FLAGS	= -I./SFML-2.5.1_gcc/include -L./SFML-2.5.1_gcc/lib -L./lib -lmy -lm

LINKER	= -L./SFML-2.5.1_gcc/lib -lsfml-graphics -lsfml-window -lsfml-system -L./lib -lmy

#-Wl, -rpath=./SFML-2.5.1_gcc/lib
#-fno-diagnostics-show-labels -fno-diagnostics-show-labels fdiagnostics-generate-patch -Wall -Wextra
#fsyntaxe-only


all:
	make -C ./lib build
	g++ -c $(SRC) $(FLAGS)
	g++ *.o -o $(NAME) $(LINKER)
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
	#rm -f $(NAME)
	make -C ./lib fclean
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.html
	rm -f vgcore.*
	rm -f callgrind.*

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
