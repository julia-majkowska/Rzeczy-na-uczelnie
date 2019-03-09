CC = g++ -std=c++11   

splay: splay.o 
	$(CC)  splay.o -o splay

splay.o: splay.cpp tree_vert.h
	$(CC) splay.cpp -c -o splay.o

black_red: black_red.o
	$(CC) black_red.o -o black_red

black_red.o: black_red.cpp tree_vert.h
	$(CC) black_red.cpp -c -o black_red.o
#tree_vert.o: tree_vert.h tree_vert.tpp
#	$(CC) tree_vert.h -c -o tree_vert.o
