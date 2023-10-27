all: sniff.c gen.c
	gcc -o sniff sniff.c
	gcc -o gen gen.c

clean:
	rm -rf sniff gen