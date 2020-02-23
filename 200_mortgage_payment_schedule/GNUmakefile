
CFLAGS := -Wall -g -Werror

BINS := $(patsubst %.c, %, $(wildcard *.c))


build: $(BINS)


BINS: %: %.o
	$(CXX) $(CFLAGS) -o $@ $<


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o $(BINS)


cleaner: clean
