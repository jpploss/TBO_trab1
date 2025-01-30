comp:
	gcc *.c -o prog
run:
	./prog
runv:
	valgrind --leak-check=full ./prog