targets = 2_1_firstThread
CFLAGS = -O3
LDFLAGS = -pthread

all: $(targets)

%.s: %c
	$(CC) -O3 -S $<

.PHONY: clean
clean:
	rm -f $(targets)
