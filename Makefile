
# File: Makefile.mak

all: raycast.o json.o ppmrw_io.o
	gcc raycast.o json.o ppmrw_io.o -o raycast
	
raycast.o: raycast.c
	gcc -c raycast.c
	
json.o: json.c json.h
	gcc -c json.c
	
ppmrw_io.o: ppmrw_io.c ppmrw_io.h
	gcc -c ppmrw_io.c

clean:
	rm *.o raycast
