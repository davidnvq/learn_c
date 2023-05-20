run:
	gcc -o chau projectC.c
	./chau

sim:
	rm -f sim
	gcc -o sim simple.c
	./sim
