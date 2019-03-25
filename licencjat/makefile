CC = g++ -std=c++11   

splay: splay.o 
	$(CC)  splay.o -o splay

splay.o: splay.cpp tree_vert.h splay.h
	$(CC) splay.cpp -c -o splay.o

black_red: black_red.o
	$(CC) black_red.o -o black_red

black_red.o: black_red.cpp tree_vert.h br_tree.h
	$(CC) black_red.cpp -c -o black_red.o
	
#Dgen: Dgen.cpp
#	$(CC) Dgen.cpp -c -o Dgen
#	
brut_split_join: brut_split_join.cpp
	$(CC) brut_split_join.cpp -o brut_split_join
	
black_red2: black_red2.o
	$(CC) black_red2.o -o black_red2
	
black_red2.o: black_red2.cpp tree_vert.h br_tree.h
	$(CC) black_red2.cpp -c -o black_red2.o
#tree_vert.o: tree_vert.h tree_vert.tpp
#	$(CC) tree_vert.h -c -o tree_vert.o
