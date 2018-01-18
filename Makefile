all:	icallib.so
list:	libllist.a
parser:	libcparse.a

libllist.a:	src/LinkedListAPI.c
	gcc -c -std=gnu11 -Iinclude src/LinkedListAPI.c -o bin/liblist.a

icallib.so:	src/CalendarParser.c src/LinkedListAPI.c
	gcc -fPIC -shared -Wall -std=gnu11 -Iinclude src/CalendarParser.c src/LinkedListAPI.c -o ./bin/icallib.so

libcparse.so:	src/CalendarParser.c src/LinkedListAPI.c
	gcc -fPIC -shared -Wall -std=gnu11 -Iinclude src/CalendarParser.c src/LinkedListAPI.c -o ./bin/icallib.so

A2main:	src/A2main.c src/CalendarParser.c src/LinkedListAPI.c
	gcc -std=gnu11 -Iinclude src/CalendarParser.c src/LinkedListAPI.c src/A2main.c -o ./bin/A2main

clean:
	rm -f bin/*.o bin/*.so bin/*.a
