targets = 2_6_firstThread3_no_thread_exit 2_7_firstThread3_pthread_join
CFLAGS = -O3
LDFLAGS = -pthread

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
