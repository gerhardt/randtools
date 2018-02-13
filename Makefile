all: getslices calcentropy

getslices:
	gcc -O2 -o getslices getslices.c

calcentropy:
	gcc -O2 -o calcentropy calcentropy.c -lm

clean:
	rm -f getslices calcentropy
