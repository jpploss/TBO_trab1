comp:
	gcc main.c node.c grafo.c dijkstra.c -o trab1
run:
	./trab1
runv:
	valgrind --leak-check=full ./trab1