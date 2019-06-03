CC = g++ -std=c++11 -g

splay: splay.o 
	$(CC)  splay.o -o splay

splay.o: splay.cpp tree_vert.h splay.h
	$(CC) splay.cpp -c -o splay.o

black_red: black_red.o
	$(CC) black_red.o -o black_red

black_red.o: black_red.cpp tree_vert.h br_tree.h br_vert.h
	$(CC) black_red.cpp -c -o black_red.o
	
brut_split_join: brut_split_join.cpp
	$(CC) brut_split_join.cpp -o brut_split_join
	
black_red2: black_red2.o
	$(CC) black_red2.o -o black_red2
	
black_red2.o: black_red2.cpp tree_vert.h br_tree.h br_vert.h
	$(CC) black_red2.cpp -c -o black_red2.o

tango: tango.o
	$(CC) tango.o -o tango

tango.o: tango.cpp tango.h tango_vert.h br_tree.h br_vert.h tree_vert.h
	$(CC) tango.cpp -c -o tango.o
	
splay_time: splay_time.o 
	$(CC)  splay_time.o -o splay_time

splay_time.o: splay_time.cpp tree_vert.h splay.h
	$(CC) splay_time.cpp -c -o splay_time.o

static_optimal: static_optimal.o 
	$(CC)  static_optimal.o -o static_optimal

static_optimal.o: static_optimal.cpp tree_vert.h static_tree.h
	$(CC) static_optimal.cpp -c -o static_optimal.o
	

time_all: time_all.o 
	$(CC)  time_all.o -o time_all

time_all.o: time_all.cpp tree_vert.h splay.h br_tree.h br_vert.h tango_vert.h tango.h
	$(CC) time_all.cpp -c -o time_all.o


time_ops: time_ops.o 
	$(CC)  time_ops.o -o time_ops

time_ops.o: time_ops.cpp tree_vert.h splay.h br_tree.h br_vert.h tango_vert.h
	$(CC) time_ops.cpp -c -o time_ops.o

time3: time3.o 
	$(CC)  time3.o -o time3

time3.o: time3.cpp tree_vert.h splay.h br_tree.h br_vert.h
	$(CC) time3.cpp -c -o time3.o
	
clean:
	rm -f *.o
