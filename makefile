comp:
	gcc main.c heap.c node.c listAdj.c dijkstra.c -o prog
run:
	./prog
runv:
	valgrind --leak-check=full ./prog