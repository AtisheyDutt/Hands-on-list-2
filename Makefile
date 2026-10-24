# Build every program:  make        Clean:  make clean
SRCS := $(wildcard *.c)
BINS := $(SRCS:.c=)

all: $(BINS)

%: %.c
	$(CC) -Wall -pthread -o $@ $<

clean:
	rm -f $(BINS) ticket.txt fifo_* myfifo22
