##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## My makefile
##

SOURCE	=	lld/*.c \
			mat/*.c

OBJ		=	$(SOURCE:.c=.o)

all:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../

build:
	gcc -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../

buildO6:
	gcc -c $(SOURCE) -O6
	ar rc libmy.a *.o
	cp libmy.a ../
	rm -f *.o

clean:
	rm -f *.o

fclean:
	rm -f *.o
	rm -f libmy.a
	rm -f ../libmy.a

re: clean all

valgrind: fclean
	gcc -g -c $(SOURCE)
	ar rc libmy.a *.o
	cp libmy.a ../
	rm -f *.o
