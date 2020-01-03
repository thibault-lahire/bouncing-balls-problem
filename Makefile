_GUI = $(if $(NOGUI),,-D GUI)
CC = gcc
CFLAGS = -std=c99 -Wall -g -I ./include $(_GUI)
LDFLAGS = -lm -lSDL2

.PHONY: clean doc

doc: conf/doxygen.conf
	doxygen conf/doxygen.conf
	firefox doc/html/index.html

clash-alea: src/clash-of-particles-alea.c src/disc.c src/event.c src/particule.c src/simulation.c src/heap.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clash-select: src/clash-of-particles-select.c src/disc.c src/event.c src/particule.c src/simulation.c src/heap.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test-particules: src/test-particle.c src/particule.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test-load: src/test-loader.c src/disc.c src/event.c src/particule.c src/simulation.c src/heap.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test-heap-correctness: src/test-heap-correctness.c src/disc.c src/event.c src/particule.c src/simulation.c src/heap.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test-heap-complexity: src/test-heap-complexity.c src/disc.c src/event.c src/particule.c src/simulation.c src/heap.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run-clash-select: clash-select
	./clash-select

run-clash-alea: clash-alea
	./clash-alea

run-test-particules: test-particules
	./test-particules

run-test-load: test-load
	./test-load

run-test-heap-correctness: test-heap-correctness
	./test-heap-correctness
	
run-test-heap-complexity: test-heap-complexity
	./test-heap-complexity
	
add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	- rm -f *.o *.csv fact.txt read-file write-fact snow ./clash-alea ./clash-select ./test-heap-complexity ./test-heap-correctness ./test-particules ./test-load
