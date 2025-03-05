comp:
	gcc main.c node.c grafo.c dijkstra.c linked-list.c -o trab1
run:
	./trab1 casos_teste_v3/caso_teste_pequeno_4.txt teste.txt
runv:
	valgrind --leak-check=full ./trab1