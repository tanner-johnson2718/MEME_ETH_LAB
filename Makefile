all: raw.c
	gcc -o raw raw.c

clean:
	rm -rf raw