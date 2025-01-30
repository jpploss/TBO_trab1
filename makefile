comp:
	gcc *.c -o prog
run:
	./prog
runV:
	valgrind --leak-check=full ./prog