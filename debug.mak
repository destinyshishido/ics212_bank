debug: user_interface.o llist.o
	g++ -DDEBUGMODE -o project_debug user_interface.o llist.o

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
