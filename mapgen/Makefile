

all: genmap
	
create_map: create_map.c
	gcc -Wall --std=gnu99 -o create_map create_map.c

genmap: genmap.c
	gcc -Wall --std=gnu99 -o genmap genmap.c

clean:
	rm -rvf *.o genmap
