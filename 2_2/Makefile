targets = 2_2_firstThread2 2_4_firstThread_loop_count_reverse 2_5_firstThread2_exit
CFLAGS = -O3
LDFLAGS = -pthread

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
