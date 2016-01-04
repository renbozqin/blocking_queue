CC=g++
CFLAGES=-std=c++11
LIBRARY=-lpthread 

test:test.o blocking_queue.o
	$(CC) $(CFLAGES) $^ -o $@ $(LIBRARY)
test.o:test.cpp
	$(CC) $(CFLAGES) -c $<
blocking_queue.o:blocking_queue.cpp
	$(CC) $(CFLAGES) -c $<

clean:
	rm *.o test


